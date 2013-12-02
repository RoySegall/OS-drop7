<?php

/**
 * @file
 * The class for "Publication By Year" type widgets.
 */

class os_boxes_pub_year extends os_boxes_default {
  /**
   * Implementation of boxes_content::options_defaults().
   */
  public function options_defaults() {
    $options = parent::options_defaults();

    $options['display_num'] = 1;

    return $options;
  }

  /**
   * Implementation of boxes_content::options_form().
   */
  public function options_form(&$form_state){
    $form = parent::options_form($form_state);

    $form['display_num'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display number of items in category'),
      '#default_value' => $this->options['display_num'],
    );
    return $form;
  }

  /**
   * Implementation of boxes_content::render().
   */
  public function render() {
    //@todo
    $block = parent::render();

    $delta = 'publication_years-block';
    list($name, $display_id) = explode('-', $delta);
    if ($view = views_get_view($name)) {
      if ($view->access($display_id)) {
        $view->set_display('block');

        //Tie this view to this box (this tells the view to call this box's view alter)
        $view->dom_id = "boxes-".$this->delta;

        //Set the display num in the view (the count)
        $arguments = $view->display_handler->get_option('arguments');
        $arguments['biblio_year']['summary_options']['count'] = ($this->options['display_num'])?1:0;
        $view->display_handler->override_option('arguments', $arguments);

        $output = $view->execute_display($display_id);
        $block['content'] = $output['content'];
      }
      $view->destroy();
    }

    return $block;
  }

  /**
   * Return the cache parameters for this box
   */
  public function cache_info(){

//    //Clear when biblio nodes are saved
//    $cache_key = array(
//      'os_og' => array('current' => 'current'),
//      'node' => array('biblio' => 'biblio'),
//    );
//
//    return array('type' => BLOCK_CACHE_CONTENT_CACHE, 'keys' => $cache_key);

  	 return array(); //caching disabled so ajax pager gets init'ed
  }

}