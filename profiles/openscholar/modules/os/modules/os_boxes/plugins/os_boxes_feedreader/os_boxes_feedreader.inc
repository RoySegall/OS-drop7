<?php

/**
 * @file
 * The class for "Feed Reader" type widgets.
 */
class os_boxes_feedreader extends os_boxes_default {

  /**
   * Implementation of boxes_content::options_defaults().
   */
  public function options_defaults(){
    $options = parent::options_defaults();

    $options['feed'] = false;
    $options['number_of_items'] = 5;
    $options['feed_display'] = 'title';

    return $options;
  }

  /**
   * Implementation of boxes_content::options_form().
   */
  public function options_form(&$form_state){
    $options = array();

    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')->propertyCondition('status', 1)->propertyCondition('type', 'feed')->propertyOrderBy('title');

    // Restrict to this site
    if (module_exists('vsite') && $space = spaces_get_space()) {
      $query->fieldCondition(OG_AUDIENCE_FIELD, 'target_id', $space->id);
    }

    $result = $query->execute();

    $form = parent::options_form($form_state);

    if (! isset($result['node']) || ! count($result['node'])) {
      $form['error'] = array(
        '#type' => 'item',
        '#title' => t('No feeds found.'),
        '#markup' => t('You must create a feed first before using this widget. ') . l("Create Feed", 'node/add/feed')
      );

      return $form;
    }

    $nodes = node_load_multiple(array_keys($result['node']));
    foreach ( $nodes as $nid => $node ) {
      // First 25 chars of title
      $options[$nid] = substr($node->title, 0, 25);
    }

    $form['feed'] = array(
      '#type' => 'select',
      '#title' => t('Feed'),
      '#options' => $options,
      '#required' => TRUE,
      '#default_value' => $this->options['feed'],
      '#description' => t('Select the feed to draw items from')
    );

    $form['feed_display'] = array(
      '#type' => 'select',
      '#title' => t('Feed item display'),
      '#options' => array('title' => t("The feed title"), 'content' => "The feed title and content summary."),
      '#required' => TRUE,
      '#default_value' => $this->options['feed_display'],
      '#description' => t('Select the way you wish the feed items to be displayed.')
    );

    $form['number_of_items'] = array(
      '#type' => 'textfield',
      '#title' => t('Number of items to display'),
      '#default_value' => $this->options['number_of_items']
    );

    $form += parent::options_form();
    return $form;
  }

  /**
   * Implementation of boxes_content::render().
   */
  public function render() {
    if (module_exists('vsite') && !vsite_get_vsite()) {
      return;
    }

    $block = parent::render();
    if (! $this->options['feed'] || ! ($node = node_load($this->options['feed']))) {
      return $block;
    }

    field_attach_prepare_view('node', array(
      $node->nid => $node
    ), 'teaser');
    entity_prepare_view('node', array(
      $node->nid => $node
    ));

    $instance = field_info_instance('node', 'field_url', 'feed');
    $display = field_get_display($instance, 'teaser', $node);
    $display['settings']['num_to_show'] = $this->options['number_of_items'];

    //Just display the title and no content summary
    $display['settings']['show_content'] = (isset($this->options['feed_display']) && ($this->options['feed_display'] == 'content'));

    $field = field_info_field_by_id($instance['field_id']);
    $result = google_feedapi_field_formatter_view('node', $node, $field, $instance, 'und', $node->field_url['und'], $display);

    $block['content'] = render($result);

    return $block;
  }

  /**
   * Return the cache parameters for this box
   */
  public function cache_info(){
  }
}
