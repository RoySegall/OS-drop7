<?php
/**
 * @file
 * os_dataverse.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function os_dataverse_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: primary-menu:data
  $menu_links['primary-menu:data'] = array(
    'menu_name' => 'primary-menu',
    'link_path' => 'data',
    'router_path' => 'data',
    'link_title' => 'Data',
    'options' => array(
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Data');


  return $menu_links;
}
