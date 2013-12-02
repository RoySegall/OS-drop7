<?php

/**
 * @file
 * Provides class for os_boxes_tabs.
 */

/**
 * Provides class for os_boxes_tabs.
 */
class os_boxes_tabs extends os_boxes_default {

  /**
   * Implements boxes_content::options_defaults().
   */
  public function options_defaults() {
    $options = parent::options_defaults();
    $options['tabs'] = array();
    return $options;
  }

  /**
   * Implements boxes_content::options_form().
   */
  public function options_form(&$form_state) {
    $form = parent::options_form($form_state);

    $form['#attached'] = array(
      'library' => array(
        array('system', 'ui.tabs'),
      ),
      'js' => array(
        drupal_get_path('module', 'os_boxes') . '/plugins/os_boxes_tabs/os_boxes_tabs_form.js',
      ),
      'css' => array(
        drupal_get_path('module', 'os_boxes') . '/plugins/os_boxes_tabs/os_boxes_tabs.css',
      ),
    );

    $widgets = module_invoke_all('os_widget');

    // filter out factories
    $options = array('os_boxes_tabs-remove' => t('No Widget'));
    ctools_include('layout', 'os');
    foreach ($widgets as $wgt => $info) {
      if (isset($info['info'])) {
        // not everything we get back from hook_os_widget has an info field.
        $options[$wgt] = $info['info'];
      }
    }

    $existing = $this->options['tabs'];
    if (!count($existing)) {
      $existing[] = array(
        'type' => 'block',
        'title' => t('First Tab'),
        'weight' => 0,
        'delta' => 'os_boxes_tabs-remove',
        'bid' => 'first-tab',
      );
    }
    $new_tab = array(
      'type' => 'block',
      'title' => 'New Tab',
      // special case
      'weight' => '200000 new',
      'delta' => 'os_boxes_tabs-remove',
      'bid' => '__blank__',
    );
    $tabs_data = array_merge($existing, array('new' => $new_tab));

    $links = array();

    $form['tabs'] = array(
      '#type' => 'container',
      '#attributes' => array('id' => 'tabs'),
      '#tree' => TRUE,
      '#description' => t('Drag the tabs to reorder them. Whichever tab is on the left will be the open tab when a user visits the page.'),
    );
    foreach ($tabs_data as $k => $t) {
      $id = 'tab-' . $k;
      $links[$t['weight']] = array(
        'href' => '',
        'fragment' => $id,
        'external' => TRUE,
        'title' => $t['title'],
      );

      $form['tabs'][$id] = array(
        '#type' => 'fieldset',
        '#attributes' => array('id' => $id, 'class' => array('panel')),
        '#weight' => 1,
        'bid' => array(
          '#type' => 'select',
          '#title' => t('Widget to Display in this Tab'),
          '#options' => $options,
          '#default_value' => $t['bid'],
          '#description' => t('Choose which widget to display in this tab. Select \'No Widget\' to remove this tab.'),
          '#attributes' => array('class' => array('tab-delta')),
        ),
        'title' => array(
          '#title' => t('Title of the Tab'),
          '#type' => 'textfield',
          '#default_value' => $t['title'],
          // for js
          '#attributes' => array('class' => array('tab-title')),
        ),
        'weight' => array(
          '#type' => 'hidden',
          '#default_value' => $t['weight'],
          // for js
          '#attributes' => array('class' => array('tab-weight')),
        ),
        'type' => array(
          '#type' => 'value',
          '#value' => 'block',
        ),
      );
    }

    ksort($links);
    $form['tabs']['links'] = array(
      '#theme' => 'links',
      '#links' => $links,
      '#attributes' => array(
        'class' => array('links'),
      ),
      '#weight' => 0,
    );

    // stores the number of real tabs
    // as soon as user picks a widget, this is incremented with js
    $form['tab_count'] = array(
      '#type' => 'hidden',
      '#default_value' => count($existing),
      '#process' => array('os_modal_tabbed_add_new_tabs'),
      '#attributes' => array(
        'id' => 'edit-count',
      ),
    );

    return $form;
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
    module_load_include('module', 'block', 'block');
    foreach ($this->options['tabs'] as $k => & $tab) {
      if ($block_tab = $blocks[$tab['bid']]) {
        if ($block_arr = _block_render_blocks(array($block_tab))) {
          if (!empty($block_arr["{$block_tab->module}_{$block_tab->delta}"]->content)) {
            $block_obj = &$block_arr[$block_tab->module . '_' . $block_tab->delta];
            $block_obj->region = $this->delta;

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

/**
 * Includes new (dynamically added) tabs in form processing.
 *
 * After submission, the form has no idea how many tabs were added through js
 * I find out here and add new form elements for each new one.
 * This form element is placed before tabs so that the new elements go
 * through the builder properly. Removing a tab is handled in the submit.
 * Removing a tab and adding a new one should handle the same as editting an existing
 */
function os_modal_tabbed_add_new_tabs(&$element, &$form_state, &$form) {
  for ($i = $element['#default_value']; $i < $element['#value']; $i++) {
    $new_tab = 'tab-' . $i;
    $form['options']['tabs'][$new_tab] = array(
      '#attributes' => array('id' => $i),
      '#parents' => array('tabs', $new_tab),
      '#array_parents' => array('options', 'tabs', $new_tab),
      '#tree' => TRUE,
    );
    $form['options']['tabs'][$new_tab] += $form['options']['tabs']['tab-new'];
    foreach ($form['options']['tabs'][$new_tab] as $key => & $child) {
      if (strpos($key, '#') !== 0) {
        unset($child['#parents']);
        unset($child['#name']);
        unset($child['#value']);
      }
    }
    form_builder($form['form_id']['#value'], $form['options']['tabs'][$new_tab], $form_state);
  }
  unset($form_state['values']['tabs']['tab-new']);

  // Removes nids that aren't in the post
  if (is_array($form_state['values'])) {
    foreach ($form_state['values']['tabs'] as $k => $v) {
      if (!isset($form_state['input']['tabs'][$k]) || !isset($form_state['input']['tabs'][$k]['bid']) || $form_state['input']['tabs'][$k]['bid'] == 'os_boxes_tabs-remove') {
        unset($form_state['values']['tabs'][$k]);
      }
    }
  }
  return $element;
}

