<?php
/**
 * @file
 * os_comments.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function os_comments_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "fb_social" && $api == "fb_social") {
    return array("version" => "1");
  }
}
