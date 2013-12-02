<?php
// $Id$


/**
 * @file
 * os_image_gallery.box.inc
 */

/**
 * Implements hook_default_box().
 */
function os_image_gallery_default_box() {
  $export = array();

  $box = new stdClass();
  /* Edit this to true to make a default box disabled initially */
  $box->disabled    = FALSE;
  $box->api_version = 1;
  $box->delta       = 'os_image_gallery_latest';
  $box->plugin_key  = 'os_sv_list_box';
  $box->title       = 'Recent Images';
  $box->description = 'Recent Images';
  $box->options     = array(
    'content_type' => 'image',
    'display' => 'display_image',
    'more' => 1,
    'more_text' => 'More',
    'more_link' => 'galleries',
    'pager' => 0,
    'number_of_items' => '6',
    'sort_by' => 'sort_newest',

    'biblio_show_all' => TRUE,
    'biblio_whitelist' => array('all' => 'all'),
  );
  $export['os_image_gallery_latest'] = $box;

  return $export;
}

