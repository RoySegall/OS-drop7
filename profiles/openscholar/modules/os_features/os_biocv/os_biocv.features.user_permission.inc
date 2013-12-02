<?php
// $Id$

/**
 * @file
 * os_biocv.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function os_biocv_user_default_permissions() {
  $permissions = array();

  // Exported permission: create bio content.
  $permissions['create bio content'] = array(
    'name' => 'create bio content',
    'roles' => array(
      0 => 'administrator',
      1 => 'manager',
      2 => 'vsite admin',
      3 => 'vsite user',
      4 => 'content editor',
    ),
    'module' => 'node',
  );

  // Exported permission: create cv content.
  $permissions['create cv content'] = array(
    'name' => 'create cv content',
    'roles' => array(
      0 => 'administrator',
      1 => 'manager',
      2 => 'vsite admin',
      3 => 'vsite user',
      4 => 'content editor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any bio content.
  $permissions['delete any bio content'] = array(
    'name' => 'delete any bio content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any cv content.
  $permissions['delete any cv content'] = array(
    'name' => 'delete any cv content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own bio content.
  $permissions['delete own bio content'] = array(
    'name' => 'delete own bio content',
    'roles' => array(
      0 => 'administrator',
      1 => 'manager',
      2 => 'vsite admin',
      3 => 'vsite user',
      4 => 'content editor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own cv content.
  $permissions['delete own cv content'] = array(
    'name' => 'delete own cv content',
    'roles' => array(
      0 => 'administrator',
      1 => 'manager',
      2 => 'vsite admin',
      3 => 'vsite user',
      4 => 'content editor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any bio content.
  $permissions['edit any bio content'] = array(
    'name' => 'edit any bio content',
    'roles' => array(
      0 => 'administrator',
      1 => 'content editor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any cv content.
  $permissions['edit any cv content'] = array(
    'name' => 'edit any cv content',
    'roles' => array(
      0 => 'administrator',
      1 => 'content editor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own bio content.
  $permissions['edit own bio content'] = array(
    'name' => 'edit own bio content',
    'roles' => array(
      0 => 'administrator',
      1 => 'manager',
      2 => 'vsite admin',
      3 => 'vsite user',
      4 => 'content editor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own cv content.
  $permissions['edit own cv content'] = array(
    'name' => 'edit own cv content',
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

