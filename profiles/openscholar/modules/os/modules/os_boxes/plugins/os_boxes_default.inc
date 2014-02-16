<?php

/**
 * @file
 * The base class for OS custom widgets. It defines an "abstract box"
 * to be extended by  "real boxes" like "listings", "feeds", "images" etc.
 *
 * It provides the widget visibility optoins. Users will decide where the
 * widget will be shown (i.e. in the current section / feature or everywhere in
 * the site
 *
 * One idea would be to even remove the widget visiblity options from here and
 * let the higher layers to deal with it
 */


abstract class os_boxes_default extends boxes_box {

  /**
   * If this box has been overridden the changed timestamp will be held here
   */
  public $changed;

  /**
   * Given an embed type, return a label
   */
  public function embed_label($type) {
    $types = &drupal_static(__FUNCTION__, array(
      'inline' => t('HTML5'),
      'iframe' => t('Iframe'),
      'oembed' => t('URL')
    ));

    if (isset($types[$type])) {
      return $types[$type];
    }
    return '';
  }

  /**
   * Implementation of boxes_content::options_defaults().
   */
  public function options_defaults() {
    return array(
      'make_embeddable' => false,
    );
  }

  /**
   * Implementation of boxes_content::options_form().
   */
  public function options_form(&$form_state) {
    $form = array();

    $form['make_embeddable'] = array(
      '#type' => 'checkbox',
      '#title' => t('Make Embeddable'),
      '#description' => t('Allow this widget to be embedded on other websites.'),
      '#default_value' => (isset($this->options['make_embeddable'])) ? $this->options['make_embeddable'] : FALSE,
      '#access' => !empty($this->embed_as),
      '#weight' => 9001,
    );

    $form['advanced'] = array(
      '#type' => 'fieldset',
      '#access' => user_access('use boxes advanced settings'),
      '#title' => t('Advanced Settings'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#weight' => 1000,
      '#after_build' => array('_os_boxes_default_advanced_handler'),
    );

    return $form;
  }

  /**
   * Implementation of boxes_content::render().
   */
  public function render() {
    $title = isset($this->title) ? $this->title : NULL;
    $block['title'] = $title;
    $block['delta'] = $this->delta;
    $block['content'] = '';
    if (!empty($this->options['make_embeddable'])) {
      $block['embed_link'] = true;
    }
    return $block;
  }
}

function _os_boxes_default_advanced_handler($element, $form_state) {
  $children = element_children($element);
  if (empty($children)) {
    $element['#access'] = false;
  }

  return $element;
}
