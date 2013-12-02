<?php
// $Id$


/**
 * @file
 * os_publications.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function os_publications_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: primary-menu:publications
  $menu_links['primary-menu:publications'] = array(
    'menu_name' => 'primary-menu',
    'link_path' => 'publications',
    'router_path' => 'publications',
    'link_title' => 'Publications',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Publications');


  return $menu_links;
}

