<?php
/**
 * @file
 * os_profiles.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function os_profiles_user_default_permissions() {
  $permissions = array();

  // Exported permission: bypass redirection.
  $permissions['bypass redirection'] = array(
    'name' => 'bypass redirection',
    'roles' => array(
      0 => 'vsite admin',
    ),
    'module' => 'field_redirection',
  );

  // Exported permission: create person content.
  $permissions['create person content'] = array(
    'name' => 'create person content',
    'roles' => array(
      0 => 'administrator',
      1 => 'manager',
      2 => 'vsite admin',
      3 => 'vsite user',
      4 => 'content editor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any person content.
  $permissions['delete any person content'] = array(
    'name' => 'delete any person content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own person content.
  $permissions['delete own person content'] = array(
    'name' => 'delete own person content',
    'roles' => array(
      0 => 'administrator',
      1 => 'manager',
      2 => 'vsite admin',
      3 => 'vsite user',
      4 => 'content editor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any person content.
  $permissions['edit any person content'] = array(
    'name' => 'edit any person content',
    'roles' => array(
      0 => 'administrator',
      1 => 'content editor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own person content.
  $permissions['edit own person content'] = array(
    'name' => 'edit own person content',
    'roles' => array(
      0 => 'administrator',
      1 => 'manager',
      2 => 'vsite admin',
      3 => 'vsite user',
      4 => 'content editor',
    ),
    'module' => 'node',
  );

  return $permissions;
}
