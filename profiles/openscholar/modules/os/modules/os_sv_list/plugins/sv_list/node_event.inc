<?php 

/**
 * @file node_event.inc
 * 
 * event plugin for sv_list box
 */

$plugin = array(
  'handler' => array('class' => 'sv_list_node_event'),
  'entity_type' => array('node'),
  'bundle' => array('event'),
);

class sv_list_node_event extends sv_list_plugin  {
  /**
   * @function register_sorts()
   *
   * Adds a custom sort for this entity/bundle
   */
  public function register_sorts() {
    return array('sort_event' => t('Event Date'));
  }
  
  /**
   * @function sort_event
   * 
   * Custom sort for events.  Uses event date, but only for
   * upcoming events that haven't taken place yet.
   */
  public function sort_event($options, $efq) {
    $efq->fieldOrderBy('field_date', 'value');
    $efq->fieldCondition('field_date', 'value2', date('Y-m-d'), '>=');
  }
  
  /**
   * @function entities_alter
   * 
   * Events have been loaded, but repeated events are grouped under a single node.
   * Split them into several nodes, then re-sort and slice them.
   */
  public function entities_alter($options, &$entities) {
    if ($options['content_type'] != 'event' || $options['sort_by'] != 'sort_event') {
      return;
    }
    
    //split repeated event into many nodes - one for each instance of event
    //key them by timestamp for easy sorting.
    $exploded = array();
    $now = strtotime(date('Y-m-d'));
    foreach ($entities as $entity) {
      foreach ($entity->field_date[LANGUAGE_NONE] as $delta => $date) {
        $time_index = strtotime($date['value']);
        while (array_key_exists($time_index, $exploded)) {
          $time_index += 1; //don't clobber events that start at same time.
        }
        
        if (max(strtotime($date['value'] . ' ' . $date['timezone']), strtotime($date['value2'] . ' ' . $date['timezone'])) >= $now) {
          $new = clone $entity;
          $new->field_date[LANGUAGE_NONE][0] = $date;
          $new->date_id = implode('.', array('date', $new->nid, 'field_date', $delta));   
          $exploded[$time_index] = $new;
        }
      }
    }
    
    ksort($exploded);    //now sort by timestamp
    $entities = array_slice(array_values($exploded), 0, $options['number_of_items']);  //and re-apply the item limit
  }
  
  /**
   * @function render
   * 
   * The default entity_view() render function loads new copies of the entities.
   * We can't allow that because it'll invalidate entities_alter().  Instead, 
   * just call node_view on each of them.
   */
  public function render($options, &$entities) {
    if ($options['content_type'] != 'event' || $options['sort_by'] != 'sort_event') {
      return;
    }

    $render = array();
    foreach ($entities as $node) {
      $render[] = node_view($node, $options['display']);
    }

    return $render;
  }
}
