<?php
/**
 * @file
 * os_software.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function os_software_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "boxes" && $api == "box") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  list($module, $api) = func_get_args();
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function os_software_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function os_software_node_info() {
  $items = array(
    'software_project' => array(
      'name' => t('Software Project'),
      'base' => 'node_content',
      'description' => t('A software project page. Provides a summary of project information and releases for download.'),
      'has_title' => '1',
      'title_label' => t('Project'),
      'help' => '',
    ),
    'software_release' => array(
      'name' => t('Software Release'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '0',
      'title_label' => '',
      'help' => '',
    ),
  );
  return $items;
}
