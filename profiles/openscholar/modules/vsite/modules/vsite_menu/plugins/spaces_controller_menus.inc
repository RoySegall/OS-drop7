<?php

/**
 * Spaces controller for menus module.
 *
 * This provides an override for menu_items stored in the "menu_item" table.  It replaces the standard call to
 * the menu_items table with the retrieval of a serialized array of menu items from the spaces_override table or
 * the preset.
 */
class spaces_controller_menus extends spaces_controller {

  /**
   * Set override values for a given controller object in this space.
   */
  function set($id, $value){
    // Change the order of the menu links to match core
    // Collect all the parent links, and then add all of
    // their children to the list as well.
    $value = self::sort_tree($value);
    
    return parent::set($id, $value);
  }

  /**
   * Get menu tree
   * Similar to get(), except that the menu_links are converted to a menu_tree
   *
   * @param $id
   * The id of the menu to retrieve.
   *
   * @param $environment
   * The realm of to fetch the setting for either 'space', 'preset', or
   * 'original'. Optional.
   */
  function get_menu_tree($id, $environment = NULL){
    $menu_links = $this->get($id, $environment);
    
    if ($menu_links == $id) {
      //This menu is not overridden, return the default menu
      return menu_tree_page_data($id);
    }
    elseif (is_array($menu_links)) {
      //Run the menu links through a function to build them into a menu tree
      return $this->tree_page_data($id, $menu_links);
    }
    
    return array();
  }

  // Override of load_original_values
  protected function load_original_values($id = NULL){
    if (empty($this->loaded_all['original'])) {
      
      if (! isset($id)) {
        ctools_include('menu', 'os');
        
        $menus = array();
        foreach ( os_get_menus() as $menu_name => $title ) {
          $menus[$menu_name] = $menu_name;
        }
        $this->values['original'] = $menus;
        $this->loaded_all['original'] = TRUE;
      }
      else if (! isset($this->loaded['original'][$id])) {
        $this->values['original'][$id] = $id;
        $this->loaded['original'][$id] = TRUE;
      }
    }
  }

  /**
   * Copy of menu_tree_page_data that works with a passed list of menu_links instead of querying the database
   * @param unknown_type $menu_name
   * @param unknown_type $menu_links
   */
  protected function tree_page_data($menu_name, $menu_links){
    $tree = &drupal_static('spaces_controller_menus-tree_page_data', array());
    
    // Check if the active trail has been overridden for this menu tree.
    $active_path = menu_tree_get_path($menu_name);
    // Load the menu item corresponding to the current page.
    if ($item = menu_get_item($active_path)) {
      $max_depth = MENU_MAX_DEPTH;
      
      // Generate a cache ID (cid) specific for this page.
      $cid = 'links:' . $menu_name . ':page:' . $item['href'] . ':' . $GLOBALS['language']->language . ':' . ( int ) $item['access'] . ':' . ( int ) $max_depth . ':' . hash('sha256', serialize($menu_links));
      
      if (! isset($tree[$cid])) {
        
        $tree_parameters = array(
            'min_depth' => 1,
            'max_depth' => $max_depth,
            'expanded' => array(
                0 => 0
            ),
            'active_trail' => array(
                0 => 0
            )
        );
        
        // Build the tree using the parameters; the resulting tree will be cached
        $data = $this->menu_build_tree($menu_name, $tree_parameters, $menu_links, $cid);
        
        // Check access for the current user to each item in the tree.
        menu_tree_check_access($data['tree'], $data['node_links']);
        $tree[$cid] = $data['tree'];
      }
      return $tree[$cid];
    }
    
    return array();
  }

  /**
   * copy of menu_build_tree (menu.inc)
   * Updated to work with a passed list of menu_links instead of querying the db directly
   *
   * @param string $menu_name
   * @param array $tree_parameters
   * @param array $menu_links
   * @param string $cid
   */
  protected function menu_build_tree($menu_name, $tree_parameters, $menu_links, $cid){
    $cache = cache_get($cid, 'cache_menu');
    if ($cache && isset($cache->data)) {
      return $cache->data;
    }
    
    $links = array();
    foreach ( $menu_links as $mlid => $ml ) {
      // May not return data if it is an external link
      $item = $this->get_router_data($ml['router_path']);
      
      if (is_array($item))
        $ml = array_merge($item, $ml);
      
      $links[] = $ml;
    }
    
    $data['tree'] = menu_tree_data($links);
    $data['node_links'] = array();
    menu_tree_collect_node_links($data['tree'], $data['node_links']);
    
    // Cache the data, if it is not already in the cache.
    cache_set($cid, $data, 'cache_menu');
    
    return $data;
  }

  /**
   * Return router data when given a path, false means that there is no
   * router data and the link is external.
   *
   * @param string $path
   */
  public function get_router_data($path){
    // May not return data if it is an external link
    $query = db_select('menu_router', 'm');
    $query->addTag('translatable');
    $query->fields('m', array(
        'load_functions',
        'to_arg_functions',
        'access_callback',
        'access_arguments',
        'page_callback',
        'page_arguments',
        'delivery_callback',
        'tab_parent',
        'tab_root',
        'title',
        'title_callback',
        'title_arguments',
        'theme_callback',
        'theme_arguments',
        'type',
        'description'
    ));
    $query->condition('m.path', $path);
    
    return $query->execute()->fetchAssoc();
  }
  
  /**
   * Given a full tree of menu links return a properly sorted
   * list of links.
   * 
   * With the optional parent set this can be used to retrieve a ordered subtree
   * 
   * The links to sort
   * @param array $links
   * 
   * The active tree, defaults to whole tree
   * @param array $parents
   */
  public static function sort_tree($links, $parents = array(0)){
    
    $result = array();
    foreach ($links as $mlid => $link) {
      if(in_array($link['plid'], $parents) && !in_array($mlid, $parents)){
        $result[$mlid] = $link;
      }
    }
    
    //Sort the parents by weight
    uasort($result, '_vsite_menu_sort_weight');
    
    //Check to see if there is any processing left to do
    if(!count($result) || count($result) == count($links)){
      return $result;
    }
    
    //Retrieve the children for this parent
    foreach ($result as $mlid => $link) {
      $children[] = self::sort_tree(array_diff_key($links, $result), array_merge($parents,array($mlid)));
    }
    
    $offset = 1;
    $children = array_filter($children);
    foreach ($children as $index => $tree) {
      //Add the child tree after the parent for efficient tree display
      $result = array_slice($result,0, ($offset + $index), true) + $tree + array_slice($result, ($offset + $index), null, true);
      $offset += count($tree);
    }
    
    //Return sorted list ready for save
    return $result;
  }

}
