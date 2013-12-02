<?php
/**
 * @file
 * os_help.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function os_help_user_default_permissions() {
  $permissions = array();

  // Exported permission: view advanced help popup.
  $permissions['view advanced help popup'] = array(
    'name' => 'view advanced help popup',
    'roles' => array(
      0 => 'anonymous user',
      1 => 'authenticated user',
    ),
    'module' => 'advanced_help',
  );

  // Exported permission: view advanced help topic.
  $permissions['view advanced help topic'] = array(
    'name' => 'view advanced help topic',
    'roles' => array(
      0 => 'anonymous user',
      1 => 'authenticated user',
    ),
    'module' => 'advanced_help',
  );

  return $permissions;
}
