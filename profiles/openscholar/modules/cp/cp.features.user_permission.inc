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

  // Exported permission: 'access control panel'.
  $permissions['access control panel'] = array(
    'name' => 'access control panel',
    'roles' => array(
      'administrator' => 'administrator',
      'manager' => 'manager',
      'vsite admin' => 'vsite admin',
    ),
    'module' => 'cp',
  );
  $permissions['administer redirects'] = array(
    'name' => 'administer redirects',
    'roles' => array(
      'administrator' => 'administrator',
      'manager' => 'manager',
      'vsite admin' => 'vsite admin',
    ),
    'module' => 'redirect',
  );

  return $permissions;
}
