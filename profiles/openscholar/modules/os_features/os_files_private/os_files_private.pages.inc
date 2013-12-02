<?php
// $Id$

/**
 * @file
 * OpenScholar control panel looks here for feature settings form.
 */

/**
 * Provides settings form for this feature on the Control Panel.
 */
function os_files_private_settings() {
  $form = array();

  $form['os_files_private_link'] = array(
    '#type' => 'markup',
    '#prefix' => '<p>'
      . t('Private files are only accessible to your ' . l(t('site members'), 'cp/users')) . '.'
      . '</p>'
      . '<p>'
      . l(t('Add and manage private files'), OS_FILES_PRIVATE_PATH)
      . '</p>',
  );

  return system_settings_form($form);
}