<?php

/**
 * Returns an array of links for this user in the Manage Members table.
 *
 * @param int $uid
 *   The specified user object's User ID.
 * @param int $gid
 *   The specified vsite object's OG group Node ID.
 *
 * @return array $columns
 */
function cp_user_get_member_rows($gid) {
  $rows = array();

  // Defines end-user text for these values.
  $default_status = t('Active');
  $owner_role = t('Manager');
  $role_edit_text = t('edit');
  $status_edit_text = t('remove');

  // Loads information for each member of the vsite.
  $member_uids = cp_user_get_member_uids($gid);
  foreach ($member_uids as $uid) {

    // Loads the user object in order to get first and last names if available.
    $user = user_load($uid);

    // Loads the user's full name-- first and last name.
    $name = _cp_user_get_full_name($user);

    // Checks to see if the user is the admin of this group.
    $vsite = spaces_get_space();
    // Checks if the current user is this vsite's author (owner).
    $is_owner = (bool) ($vsite->group->uid == $uid);

    // If the user is the owner, return a special row with no edit links.
    if ($is_owner) {
      $role = $owner_role;
      $role_edit_link = '';
      $status_edit_link = '';
    }

    // Otherwise, checks the current user's OG roles.
    // The member's role could be one of: Vsite admin, Content Editor, or Member.
    else {
      $human_name = TRUE;
      $role = _cp_user_get_role($uid, $vsite->group->nid, $human_name);
      $options = array('attributes' => array('class' => array('cp-user-float-right')));
      $role_edit_link = l($role_edit_text, "cp/users/edit_membership/{$uid}", $options);
      $status_edit_link = l($status_edit_text, "cp/users/delete_membership/{$uid}", $options);
    }

    // Prepare the row to be used by theme_table().
    // @see cp_user_user_management_page()
    $row = array(
      'name' => $name,
      'username' => $user->name,
      'role' => $role . $role_edit_link,
      'status' => $default_status . $status_edit_link,
    );

    $rows[] = $row;
  }

  return $rows;
}

/**
 * Returns an array containing the given vsite's members User IDs.
 *
 * @param int $gid
 *   The specified vsite object's OG group Node ID.
 *
 * @return array $members
 *   The list of members' User IDs in the specified vsite.
 */
function cp_user_get_member_uids($gid) {
  $query = db_select('og_membership', 'ogm');
  $query->condition('ogm.gid', $gid);
  $query->condition('entity_type', 'user');
  $query->fields('ogm', array('etid'));
  $results = $query->execute()->fetchAll();

  $member_uids = array();
  foreach ($results as $record => $values) {
    if (isset($values->etid) && $values->etid != 0) {
      $member_uids[] = $values->etid;
    }
  }

  return $member_uids;
}

/**
 * Page callback; returns content for the CP > People page (Manage Members).
 *
 * @param int $gid
 *   The specified vsite object's OG group Node ID.
 */
function cp_user_user_management_page($gid) {
  // Prepares end user strings for the page.
  $add_new_user_link_title = t('+ Add a member');
  $header = array(t('Name'), t('Username'), t('Role'), t('Status'));
  $rows = cp_user_get_member_rows($gid);
  $attached_css = drupal_get_path('module', 'cp_user') . '/cp_user.css';

  $build = array(
    'cp_user' => array(
      '#type' => 'container',
      '#attributes' => array(
        'id' => 'cp-user',
        'class' => array('cp-manage-users-wrapper'),
      ),
      'cp_user_actions' => array(
        '#type' => 'container',
        '#attributes' => array(
          'class' => array('cp-add-new-user')
        ),
        'cp_user_add_new' => array(
          '#theme' => 'links',
          '#links' => array(
            array(
              'title' => $add_new_user_link_title,
              'href' => 'cp/users/add',
              'attributes' => array(
                'class' => array('os-green-button', 'cp-user-float-right'),
              ),
            ),
          ),
        ),
        '#weight' => 0,
      ),
      'cp_user_main' => array(
        '#type' => 'container',
        '#attributes' => array(
          'class' => array('cp-manager-user-content')
        ),
        'cp_user_list' => array(
          '#theme' => 'table',
          '#header' => $header,
          '#rows' => $rows,
        ),
        '#weight' => 1,
      ),
    ),
    '#attached' => array(
      'css' => array(
        'type' => 'file',
        'data' => $attached_css,
      ),
    ),
  );

  return $build;
}

/**
 * Form builder; provides confirmation for "Remove Member" action.
 */
function cp_user_remove_membership_confirm($form_state, $user_load) {
  $space = spaces_get_space();
  // Form sets.
  $user = $user_load['build_info']['args'][0];
  $user_name = _cp_user_get_full_name($user);
  $site_name = $space->group->title;
  $form['gid'] = array('#type' => 'value', '#value' => $space->group->nid);
  $form['uid'] = array('#type' => 'value', '#value' => $user->uid);
  $form['user_name'] = array('#type' => 'value', '#value' => $user_name);
  $form['site_name'] = array('#type' => 'value', '#value' => $site_name);

  // Prepares necessary values for confirm_form().
  $user_name = $user_load['build_info']['args'][0]->name;

  $question = t('Remove member <em>@user</em> from site <em>@site</em>?',
    array('@user' => $user_name, '@site' => $site_name));
  $path = 'cp/users';
  $description = t('You may add a removed member back to your site at any time.');
  $yes = t('Remove');
  $no = t('Cancel');

  return confirm_form($form, $question, $path, $description, $yes, $no);
}

/**
 * Submit callback; removes the specified member after user confirms action.
 */
function cp_user_remove_membership_confirm_submit($form, &$form_state) {
  // Ungroup the user from the node
  $gid = $form_state['values']['gid'];
  $uid = $form_state['values']['uid'];
  og_ungroup('node', $gid, 'user', $uid);

  $user_name = $form_state['values']['user_name'];
  $site_name = $form_state['values']['site_name'];
  // Set the message and redirect back to the cp/users page
  drupal_set_message(t('Member <em>@user</em> has been removed from <em>@site</em>', array('@user' => $user_name, '@site' => $site_name)));
  drupal_goto('cp/users');
}

/**
 * Form builder; provides the options for the "Edit membership" form.
 */
function cp_user_edit_membership_form($form_state, $user_load) {
  $space = spaces_get_space();
  if (!isset($user_load['build_info']['args'][0]->uid)) {
    return;
  }
  $user = $user_load['build_info']['args'][0];

  // Prepares replacement value text for the modal form.
  $name = _cp_user_get_full_name($user);
  $site = $space->group->title;

  // Form sets.
  $form['gid'] = array('#type' => 'value', '#value' => $space->group->nid);
  $form['bundle'] = array('#type' => 'value', '#value' => $space->group->type);
  $form['uid'] = array('#type' => 'value', '#value' => $user->uid);
  $form['user_name'] = array('#type' => 'value', '#value' => $name);
  $form['site_name'] = array('#type' => 'value', '#value' => $site);
  $form['title'] = array(
    '#type' => 'markup',
    '#markup' => t('<h2>Editing member <em>@name</em></h2>', array('@name' => $name)),
    '#weight' => 0,
  );
  $form['edit_membership'] = array(
    '#type' => 'fieldset',
    '#title' => t('Role:'),
    '#weight' => 10,
  );
  // Prepares the list mode to generate verbose role descriptions on options.
  $list_mode = 'options';
  $form['edit_membership']['edit_role'] = array(
    '#type' => 'radios',
    '#options' => _cp_user_list_roles($list_mode),
    '#default_value' => _cp_user_get_role($user->uid, $space->group->nid),
  );

  // Builds and returns a confirmation form.
  $question = t('Editing members for site <em>@site</em>', array('@name' => $name, '@site' => $site));
  $path = 'cp/users';
  $description = ' ';
  $yes = t('Save');
  $no = t('Cancel');
  return confirm_form($form, $question, $path, $description, $yes, $no);
}

/**
 * Submit callback; updates roles after user confirms action.
 */
function cp_user_edit_membership_form_submit($form, &$form_state) {
  // Accesses values from the form.
  $bundle = $form_state['values']['bundle'];
  $new_role = $form_state['values']['edit_role'];
  $gid = $form_state['values']['gid'];
  $uid = $form_state['values']['uid'];
  // Grants the new role and revokes other roles.
  _cp_user_set_role($uid, $gid, $new_role, $bundle);

  // Set the message and redirect back to the cp/users page
  $user = $form_state['values']['user_name'];
  $site = $form_state['values']['site_name'];
  drupal_set_message(t('User <em>@user\'s</em> role on site <em>@site</em> was updated successfully.', array('@user' => $user, '@site' => $site)));
  drupal_goto('cp/users');
}

/**
 * Returns a name like "First Last (username)", or else username if none found.
 *
 * @param object $user
 *   The fully loaded user object.
 *
 * @return string $name
 *   The user's full name, or username if none found.
 */
function _cp_user_get_full_name($user) {
  // Tries to get the user's first and last name, otherwise uses username.
  // Gets the first name field's safe value.
  $items = field_get_items('user', $user, 'field_first_name');
  if (isset($items[0]['safe_value'])) {
    $first_name = $items[0]['safe_value'];
  }
  else {
    $first_name = '';
  }
  // Gets the last name field's safe value.
  $items = field_get_items('user', $user, 'field_last_name');
  if (isset($items[0]['safe_value'])) {
    $last_name = $items[0]['safe_value'];
  }
  else {
    $last_name = '';
  }
  // Uses either the full name, or the username if first and last not available.
  if ($first_name && $last_name) {
    $name = "$first_name $last_name";
  }
  else {
    $name = $user->name;
  }

  return $name;
}

/**
 * Returns a themed label and description of a role for the Manage Members page.
 */
function _cp_user_role_option($label, $description) {
  return "<strong>$label</strong><br/>$description";
}

/**
 * Returns the user's current role for this group.
 *
 * @param bool $human_name
 *   If TRUE, returns the human-readable name (i.e. "Administrator")
 *   If FALSE, returns the machine name (i.e. "vsite admin")
 */
function _cp_user_get_role($uid, $gid, $human_name = FALSE) {
  // Loads the user's roles with this group node.
  $user_roles = og_get_user_roles('node', $gid, $uid);
  // Handles vsite admins...
  if (in_array('vsite admin', $user_roles)) {
    $role = OS_USER_ROLE_ADMIN;
  }
  // Handles non-admins...
  else if (in_array('content editor', $user_roles)) {
    $role = OS_USER_ROLE_EDITOR;
  }
  else if (in_array('vsite user', $user_roles)) {
    $role = OS_USER_ROLE_BASIC;
  }
  else {
    $role = t('authenticated user');
  }

  if ($human_name) {
    $names = _cp_user_list_roles();
    $role = isset($names[$role]) ? $names[$role] : t('None');
  }

  return $role;
}

/**
 * Grants the specified role for this user on this group, and revokes others.
 * @param int $uid
 * @param int $gid
 * @param string $role_name
 */
function _cp_user_set_role($uid, $gid, $role_name, $bundle = 'personal') {
  // Gets a map of group roles with (key) role machine name => (value) role ID.
  $roles = _cp_user_list_roles('rids', $bundle);

  // Loops over each possible OG role...
  foreach ($roles as $machine_name => $rid) {
    // If this is the new role to grant the user...
    if ($role_name == $machine_name) {
      // Checks the user's current roles in this group.
      $user_roles = og_get_user_roles('node', $gid, $uid);
      // Only grants the role if the user doesn't have the role yet.
      if (empty($user_roles[$rid])) {
        og_role_grant('node', $gid, $uid, $rid);
      }
    }
    // Otherwise, we remove the non-specified role.
    // Only one role per-user-per-group allowed at a time.
    else {
      og_role_revoke('node', $gid, $uid, $rid);
    }
  }
}