<?php
/**
 * @file
 * os_classes.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function os_classes_ctools_plugin_api() {
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
function os_classes_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function os_classes_node_info() {
  $items = array(
    'class' => array(
      'name' => t('Class'),
      'base' => 'node_content',
      'description' => t('A course listing for a college or university class.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'class_material' => array(
      'name' => t('Class Material'),
      'base' => 'node_content',
      'description' => t('A post related to a class'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
