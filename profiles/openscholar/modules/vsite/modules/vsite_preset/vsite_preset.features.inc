<?php
/**
 * @file
 * vsite_preset.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function vsite_preset_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "spaces" && $api == "spaces") {
    return array("version" => "3");
  }
}
