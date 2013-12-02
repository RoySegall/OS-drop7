<?php

/**
 * @file
 * The class for "RSS" type widgets.
 */
class os_boxes_rss extends os_boxes_default {

  /**
   * Implementation of boxes_content::options_defaults().
   */
  public function options_defaults(){
    $options = parent::options_defaults();

    $options['show_all'] = true;
    $options['content'] = array();
    return $options;
  }

  /**
   * Implementation of boxes_content::options_form().
   */
  public function options_form(&$form_state){
    $form = parent::options_form($form_state);
    $form['show_all'] = array(
        '#type' => 'checkbox',
        '#title' => t('Show all content'),
        '#default_value' => $this->options['show_all'],
    );

    $types = os_get_bundles(array(2,1));
    $form['content'] = array(
        '#type' => 'checkboxes',
        '#title' => t('Content Types to Display'),
        '#default_value' => $this->options['content'],
        '#options' => array_filter($types),
        '#states' => array(
            // Hide the settings when the show all checkbox is checked.
            'invisible' => array(
                ':input[name="show_all"]' => array(
                    'checked' => TRUE
                )
            ),
        )
    );

    $form += parent::options_form($form_state);
    return $form;
  }

  /**
   * Implementation of boxes_content::render().
   */
  public function render() {
    if (module_exists('vsite') && !vsite_get_vsite()) {
      return;
    }

    // @todo
    $block = parent::render();

    $arg = '';
    $types = array_filter($this->options['content']);
    if (!$this->options['show_all'] && count($types)) {
      $arg = '/' . implode("+", $types);
    }

    if ($image = theme('image', array('path' => 'misc/feed.png', 'title' => t('Syndicate content')))) {
      $block['content'] = l($image . ' Subscribe', 'feed' . $arg, array(
          'html' => TRUE,
          'attributes' => array(
              'class' => 'feed-icon'
          )
      ));
    }

    return $block;
  }

}
