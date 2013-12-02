<?php
/**
 * @file
 * os_boxes.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function os_boxes_user_default_permissions() {
  $permissions = array();

  // Exported permission: administer boxes.
  $permissions['administer boxes'] = array(
    'name' => 'administer boxes',
    'roles' => array(
      0 => 'administrator',
      1 => 'manager',
    ),
    'module' => 'boxes',
  );

  // Exported permission: edit boxes.
  $permissions['edit boxes'] = array(
    'name' => 'edit boxes',
    'roles' => array(
      0 => 'administrator',
      1 => 'manager',
      2 => 'vsite admin',
    ),
    'module' => 'boxes',
  );

  return $permissions;
}
