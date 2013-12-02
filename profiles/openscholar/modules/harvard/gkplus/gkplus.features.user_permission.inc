<?php


/**
 * @file
 * gkplus.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function gkplus_user_default_permissions() {
  $permissions = array();

  // Exported permission: order nodes within categories.
  $permissions['order nodes within categories'] = array(
    'name' => 'order nodes within categories',
    'roles' => array(
      0 => 'administrator',
      1 => 'vsite admin',
    ),
    'module' => 'nodeorder',
  );

  return $permissions;
}