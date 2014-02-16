<?php

class os_boxes_rand_widget extends os_boxes_widget_collection {

  public $embed_as = array(
    'iframe',
  );

  public function render() {
    $block = parent::render();

    $k = array_rand($this->options['widgets']);
    $widget = $this->render_widget($k);

    $block['content'] = drupal_render($widget);

    return $block;
  }
}