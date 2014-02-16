<?php

/**
 * @file
 * Module settings and configuration administration UI.
 */

/**
 * Form definition; admin settings.
 */
function html_title_admin_settings() {
  $form['description'] = array(
    '#value' => t('Only the HTML tags below may be allowed in node titles. Any tags not enabled here will be removed. Note that all HTML will be removed in feed output and JSON output in views.'),
    '#prefix' => '<p>',
    '#suffix' => '</p>',
  );

  $form['html_title_allowed_elements'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Available tags'),
    '#default_value' => variable_get('html_title_allowed_elements', array('em', 'sub', 'sup')),
    '#options' => array(
      'em' => check_plain('<em>'),
      'sub' => check_plain('<sub>'),
      'sup' => check_plain('<sup>'),
      'i' => check_plain('<i>'),
      'b' => check_plain('<b>'),
      'strong' => check_plain('<strong>'),
    ),
  );

  return system_settings_form($form);
}
