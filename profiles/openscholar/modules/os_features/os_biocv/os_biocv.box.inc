<?php
// $Id$

/**
 * @file
 * os_biocv.box.inc
 */

/**
 * Implements hook_default_box().
 */
function os_biocv_default_box() {
  $export = array();

  $box = new stdClass();
  /* Edit this to true to make a default box disabled initially */

  $box->disabled    = FALSE;
  $box->api_version = 1;
  $box->delta       = 'bio_teaser';
  $box->plugin_key  = 'os_boxes_bio';
  $box->title       = '';
  $box->description = 'Bio';
  $box->options     = array(
    'additional_classes' => '',
    'show_title'     => 0,
    'teaser'         => 'full',
  );
  $export['bio_teaser'] = $box;

  return $export;
}

