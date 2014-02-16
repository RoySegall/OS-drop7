<?php
/**
 * @file
 * cp.form.inc
 */

/**
 * Form builder; merges various site settings into a single "Settings" form.
 */
function cp_settings_form($form_state) {
  $form = array();
  $form['#submit'] = array();
  $form['#after_build'] = array();

  // Loops over all implementations of hook_cp_settings().
  $settings = cp_get_setting_forms();
  foreach ($settings as $key => $setting) {
    if (!isset($setting['form'])) {
      continue;
    }

    // Creates any non-existing fieldgroup for this setting, if specified.
    if (isset($setting['group'])) {
      $id = $setting['group']['#id'];
      if (!isset($form[$id])) {
        $form[$id] = $setting['group'];
        $form[$id]['#type'] = 'fieldset';
      }

      $form[$id][$key] = $setting['form'];
    }
    else {
      $form[$key] = $setting['form'];
    }

    // Merges any submit handler(s) into the existing value.
    if (isset($setting['submit'])) {
      $form['#submit'] = array_merge($form['#submit'], $setting['submit']);
    }
    if (isset($setting['after_build'])) {
      $form['#after_build'] = array_merge($form['#after_build'], $setting['after_build']);
    }
  }

  return system_settings_form($form);
}
