<?php

/**
 * @file
 * The class for "Shield" type widgets.
 */

class os_shields_box extends os_boxes_default {

  /**
   * Implementation of boxes_content::options_defaults().
   */
  public function options_defaults() {
    $options = parent::options_defaults();

    $options['shield'] = variable_get('os_shields_shield', '');
    return $options;
  }

  /**
   * Implementation of boxes_content::options_form().
   */
  public function options_form(&$form_state){

    //The shield List
    $a_shields = variable_get('os_shields_shield_info', array());

    if (count($a_shields)) {
      $shield_options = array();
      $path_prefix = 'public://os_shields/';
      foreach ($a_shields as $fname => $shield)  {
        if (!$shield['hidden']) {
          $shield = file_load($shield['fid']);
          if (file_exists($shield->uri)) {
            $shield_options[$shield->filename] = theme('os_shields_theme_shieldpicker', array('file' => $shield));
          }
        }
      }

      $form['shield'] = array(
        '#prefix' => '<div class="shield_wrapper clear-block">',
        '#title' => t('Shield'),
        '#type' => 'radios',
        '#options' => $shield_options,
        '#default_value' => $this->options['shield'],
        // use the spaces original value, which should always be set as long as a shield has been uploaded
        '#suffix' => '</div>',
        '#attached' => array(
          'css' => array(
            drupal_get_path('module', 'os_shields') . '/theme/os_shields-shield-picker.css',
          ),
          'js' => array(
            drupal_get_path('module', 'os_shields') . '/theme/os_shields-shield-picker.js',
          ),
        ),
      );
    }
    if (empty($shield_options)) {
      $form['shield'] = array(
        '#type' => 'markup',
        '#value' => t('Your site has no shields to display.'),
        '#prefix' => '<div>',
        '#suffix' => '</div>',
      );
    }
  //END Shield List

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
    
    //@todo
    $block = parent::render();
    $block['subject'] = $block['title'] = '';

    $filename = isset($this->options['shield'])?$this->options['shield']:variable_get('os_shields_shield', '');
    if ($filename && file_exists('public://os_shields/'.$filename)) {
      $block['content'] = '<div id="scholar-shield"><img src="'.file_create_url('public://os_shields/'.$filename).'" alt="Shield" title="Shield" /> </div>';
    }
    else if (spaces_access_admin() && count(variable_get('os_shields_shield_info', array())) == 0) {
      $block['content'] = t('No shields have been added to your install. Contact your site administrator or remove this widget to hide this message.');
    }
    else {
      $block ['content'] = ' ';
    }
    return $block;
  }

}
