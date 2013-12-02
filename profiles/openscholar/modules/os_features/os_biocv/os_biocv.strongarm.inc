<?php
// $Id$

/**
 * @file
 * os_biocv.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function os_biocv_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_bio';
  $strongarm->value = 0;
  $export['comment_anonymous_bio'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_cv';
  $strongarm->value = 0;
  $export['comment_anonymous_cv'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_bio';
  $strongarm->value = '0';
  $export['comment_bio'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_cv';
  $strongarm->value = '0';
  $export['comment_cv'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_bio';
  $strongarm->value = 1;
  $export['comment_default_mode_bio'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_cv';
  $strongarm->value = 1;
  $export['comment_default_mode_cv'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_bio';
  $strongarm->value = '50';
  $export['comment_default_per_page_bio'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_cv';
  $strongarm->value = '50';
  $export['comment_default_per_page_cv'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_bio';
  $strongarm->value = 1;
  $export['comment_form_location_bio'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_cv';
  $strongarm->value = 1;
  $export['comment_form_location_cv'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_bio';
  $strongarm->value = '1';
  $export['comment_preview_bio'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_cv';
  $strongarm->value = '1';
  $export['comment_preview_cv'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_bio';
  $strongarm->value = 1;
  $export['comment_subject_field_bio'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_cv';
  $strongarm->value = 1;
  $export['comment_subject_field_cv'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_bio';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_bio'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_cv';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_cv'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_bio';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_bio'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_cv';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_cv'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_bio';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_bio'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_cv';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_cv'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_bio';
  $strongarm->value = '0';
  $export['node_preview_bio'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_cv';
  $strongarm->value = '0';
  $export['node_preview_cv'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_bio';
  $strongarm->value = 0;
  $export['node_submitted_bio'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_cv';
  $strongarm->value = 0;
  $export['node_submitted_cv'] = $strongarm;

  return $export;
}

