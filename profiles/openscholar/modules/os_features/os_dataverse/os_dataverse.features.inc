<?php
/**
 * @file
 * os_dataverse.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function os_dataverse_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
}
