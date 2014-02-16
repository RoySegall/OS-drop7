<?php
/**
 * @file
 * os_comments.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function os_comments_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "fb_social" && $api == "fb_social") {
    return array("version" => "1");
  }
}
