<?php
// $Id$


/**
 * Implementation of hook_menu_default_menu_links().
 */
function scholar_dvn_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: primary-menu:data
  $menu_links['primary-menu:data'] = array(
    'menu_name' => 'primary-menu',
    'link_path' => 'data',
    'router_path' => 'data',
    'link_title' => 'Data',
    'options' => array(),
    'module' => 'system',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Data');


  return $menu_links;
}

