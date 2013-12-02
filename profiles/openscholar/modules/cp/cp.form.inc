<?php
/**
 * Defines a form to display the various settings that have nowhere else to go
 */
function cp_settings_form($form_state) {
  $form = array();
  $form['#submit'] = array();

  $settings = cp_get_setting_forms();
  foreach ($settings as $key => $s) {
    if (!isset($s['form'])) continue;

    // if the setting defines a group for itself,
    // that group should be created and the form placed
    // in the group
    if (isset($s['group'])) {
      $id = $s['group']['#id'];
      if (!isset($form[$id])) {
        $form[$id] = $s['group'];
        $form[$id]['#type'] = 'fieldset';
      }

      $form[$id][$key] = $s['form'];
    }
    else {
      $form[$key] = $s['form'];
    }

    // if the form includes its own submit handlers,
    // merge them into the existing
    if (isset($s['submit'])) {
      $form['#submit'] = array_merge($form['#submit'], $s['submit']);
    }
  }

  return system_settings_form($form);
}