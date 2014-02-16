<?php 

/**
 * @file node_person.inc
 * 
 * person plugin for sv_list box
 */

$plugin = array(
  'handler' => array('class' => 'sv_list_node_person'),
  'entity_type' => array('node'),
  'bundle' => array('person'),
);

class sv_list_node_person  extends sv_list_plugin {
  
  /**
   * @function sort_alter
   * 
   * People should use last name, not first.
   */
  public function sort_alter($options, $efq) {  
    if ($options['content_type'] != 'person') {
      return;
    }
    
    if ($options['sort_by'] == 'sort_alpha') {
      $efq->order = array();
      $efq->fieldOrderBy('field_last_name', 'value', 'ASC');
      $efq->propertyOrderBy('title', 'ASC');
    }
  }
}
