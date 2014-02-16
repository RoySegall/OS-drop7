<?php

/**
 * @file
 * Provides class for os_boxes_tabs.
 */

/**
 * Provides class for os_boxes_tabs.
 */
class os_boxes_tabs extends os_boxes_widget_collection {

  public $embed_as = array(
    'iframe',
  );

  // for backwards compatibility
  public function options_defaults() {
    $options = parent::options_defaults();
    $options['tabs'] = array();
    return $options;
  }

  public function options_form(&$form_state) {
    if (!empty($this->options['tabs'])) {
      $this->options['widgets'] = $this->options['tabs'];
    }
    return parent::options_form($form_state);
  }

  /**
   * Implements render().
   */
  public function render() {
    $block = parent::render();

    $plugin = context_get_plugin('reaction', 'block');
    $blocks = $plugin->get_blocks();
    $render = array(
      'links' => array(
        '#theme' => 'links',
        '#links' => array(),
      ),
      '#attached' => array(
        'library' => array(
          array('system', 'ui.tabs'),
        ),
        'js' => array(
          drupal_get_path('module', 'os_boxes') . '/plugins/os_boxes_tabs/os_boxes_tabs_display.js',
        ),
      ),
    );

    if (!empty($this->options['tabs'])) {
      $this->options['widgets'] = $this->options['tabs'];
    }

    module_load_include('module', 'block', 'block');
    foreach ($this->options['widgets'] as $k => & $tab) {
      if ($block_tab = $blocks[$tab['bid']]) {
        $block_tab->region = $this->delta;
        if ($block_arr = _block_render_blocks(array($block_tab))) {
          if (!empty($block_arr["{$block_tab->module}_{$block_tab->delta}"]->content)) {

            $render['links']['#links'][$tab['weight']] = array(
              'title' => $tab['title'],
              'href' => '',
              'fragment' => $k,
              'external' => TRUE,
            );

            $build = _block_get_renderable_array($block_arr);
            $build['#attributes']['id'] = '';
            $render[$tab['bid']] = array(
              '#type' => 'container',
              '#attributes' => array('id' => $k),
              $tab['bid'] => $build,
            );
          }
        }
      }
    }
    ksort($render['links']['#links']);
    $block['content'] = drupal_render($render);

    return $block;
  }
}

