<?php
/**
 * @file
 * os_files_private.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function os_files_private_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
}

/**
 * Implements hook_views_api().
 */
function os_files_private_views_api() {
  return array("version" => "3.0");
}
