<?php 

/**
 * @file node_book.inc
 * 
 * book plugin for sv_list box
 */

$plugin = array(
  'handler' => array('class' => 'sv_list_node_book'),
  'entity_type' => array('node'),
  'bundle' => array('book'),
);

class sv_list_node_book  extends sv_list_plugin {
  
  /**
   * @function sort_alter
   * 
   * People should use last name, not first.
   */
  public function query_alter($options, $efq) {  
    if ($options['content_type'] != 'book') {
      return;
    }
    
    // limit book depth to 1.  not a field, so use a regular query.
    $nids = db_select('menu_links', 'ml')
      ->condition('module', 'book')
      ->condition('depth', 1)
      ->fields('ml', array('link_path'))
      ->execute()
      ->fetchCol();
    $nids = preg_replace('/node\//', '', $nids);
    $nids = array_values($nids);
    
    if ($nids) {
      $efq->propertyCondition('nid', $nids, 'IN');
    }
  }
}
