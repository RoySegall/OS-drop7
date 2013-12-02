<?php
// $Id$

/**
 * @file
 * os_classes.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function os_classes_user_default_permissions() {
  $permissions = array();

  // Exported permission: create class content.
  $permissions['create class content'] = array(
    'name' => 'create class content',
    'roles' => array(
      0 => 'administrator',
      1 => 'manager',
      2 => 'vsite admin',
      3 => 'vsite user',
      4 => 'content editor',
    ),
    'module' => 'node',
  );

  // Exported permission: create class_material content.
  $permissions['create class_material content'] = array(
    'name' => 'create class_material content',
    'roles' => array(
      0 => 'administrator',
      1 => 'manager',
      2 => 'vsite admin',
      3 => 'vsite user',
      4 => 'content editor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any class content.
  $permissions['delete any class content'] = array(
    'name' => 'delete any class content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any class_material content.
  $permissions['delete any class_material content'] = array(
    'name' => 'delete any class_material content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own class content.
  $permissions['delete own class content'] = array(
    'name' => 'delete own class content',
    'roles' => array(
      0 => 'administrator',
      1 => 'manager',
      2 => 'vsite admin',
      3 => 'vsite user',
      4 => 'content editor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own class_material content.
  $permissions['delete own class_material content'] = array(
    'name' => 'delete own class_material content',
    'roles' => array(
      0 => 'administrator',
      1 => 'manager',
      2 => 'vsite admin',
      3 => 'vsite user',
      4 => 'content editor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any class content.
  $permissions['edit any class content'] = array(
    'name' => 'edit any class content',
    'roles' => array(
      0 => 'administrator',
      1 => 'content editor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any class_material content.
  $permissions['edit any class_material content'] = array(
    'name' => 'edit any class_material content',
    'roles' => array(
      0 => 'administrator',
      1 => 'content editor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own class content.
  $permissions['edit own class content'] = array(
    'name' => 'edit own class content',
    'roles' => array(
      0 => 'administrator',
      1 => 'manager',
      2 => 'vsite admin',
      3 => 'vsite user',
      4 => 'content editor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own class_material content.
  $permissions['edit own class_material content'] = array(
    'name' => 'edit own class_material content',
    'roles' => array(
      0 => 'administrator',
      1 => 'manager',
      2 => 'vsite admin',
      3 => 'vsite user',
      4 => 'content editor',
    ),
    'module' => 'node',
  );

  return $permissions;
}

