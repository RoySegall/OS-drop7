<?php
/**
 * @file
 * cp.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cp_user_default_permissions() {
  $permissions = array();

  // Exported permission: access control panel.
  $permissions['access control panel'] = array(
    'name' => 'access control panel',
    'roles' => array(
      0 => 'administrator',
      1 => 'manager',
      2 => 'vsite admin',
    ),
    'module' => 'cp',
  );

  return $permissions;
}
