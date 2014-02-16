<?php
/**
 * @file
 * os_biocv.features.metatag.inc
 */

/**
 * Implements hook_metatag_export_default().
 */
function os_biocv_metatag_export_default() {
  $config = array();

  // Exported Metatag config instance: node:bio.
  $config['node:bio'] = array(
    'instance' => 'node:bio',
    'config' => array(
      'og:type' => array(
        'value' => 'profile',
      ),
    ),
  );

  // Exported Metatag config instance: node:cv.
  $config['node:cv'] = array(
    'instance' => 'node:cv',
    'config' => array(
      'og:type' => array(
        'value' => 'profile',
      ),
    ),
  );

  return $config;
}
