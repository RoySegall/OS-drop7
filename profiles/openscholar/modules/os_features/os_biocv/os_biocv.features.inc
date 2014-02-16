<?php
/**
 * @file
 * os_biocv.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function os_biocv_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "boxes" && $api == "box") {
    return array("version" => "1");
  }
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => "1");
  }

  if ($module == "feeds_tamper" && $api == "feeds_tamper_default") {
    return array("version" => "2");
  }

  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function os_biocv_node_info() {
  $items = array(
    'bio' => array(
      'name' => t('Bio'),
      'base' => 'node_content',
      'description' => t('A user\'s personal biography.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'cv' => array(
      'name' => t('CV'),
      'base' => 'node_content',
      'description' => t('A user\'s personal curriculum vitae.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
