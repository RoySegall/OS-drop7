<?php
// $Id$

/**
 * @file
 * os_image_gallery.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function os_image_gallery_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_media_gallery';
  $strongarm->value = 0;
  $export['comment_anonymous_media_gallery'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_media_gallery';
  $strongarm->value = 1;
  $export['comment_default_mode_media_gallery'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_media_gallery';
  $strongarm->value = '50';
  $export['comment_default_per_page_media_gallery'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_media_gallery';
  $strongarm->value = '0';
  $export['comment_media_gallery'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_media_gallery';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_media_gallery'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_media_gallery';
  $strongarm->value = FALSE;
  $export['node_submitted_media_gallery'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_media_gallery_pattern';
  $strongarm->value = 'galleries/[node:title]';
  $export['pathauto_node_media_gallery_pattern'] = $strongarm;

  return $export;
}

