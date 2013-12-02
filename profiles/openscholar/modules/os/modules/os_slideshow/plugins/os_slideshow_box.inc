<?php

class os_slideshow_box extends os_boxes_default {

  public function options_defaults() {
    $options = parent::options_defaults();

    return $options + array(
      'effect' => 'fade',
      'nodes' => array(),
      'timeout' => 5000,
      'speed' => 700,
      'random' => FALSE,
      'layout' => '3_1_overlay',
    );
  }

  public function options_form(&$form_state) {
    $form = parent::options_form($form_state);
    $defaults = $this->options_defaults();


    $layouts = _os_slideshow_layouts();
    if (!$this->new) {
      // Layouts can be changed, but the ratio is locked, limiting available
      // layouts.
      $ratio = current(array_keys($layouts[ $this->options['layout'] ]['ratio']));
    }

    foreach ($layouts as $name => $layout) {
      if ($this->new || $ratio == current(array_keys($layout['ratio']))) {
        $file = drupal_get_path('module', 'os_slideshow') . '/images/' . $name . '.png';
        $ratio_options[$name] = (file_exists($file)) ? theme('image', array('path'=>$file)) . $layout['name'] : $layout['name'];
      }
    }

    $form['layout'] = array(
      '#type' => 'radios',
      '#title' => t('Slideshow Layout'),
      '#description' => t('Slideshow images and captions will be laid out in this manner.'),
      '#required' => TRUE,
      '#options' => $ratio_options, //get these from some other function somehow
      '#default_value' => ($this->options['layout']) ? $this->options['layout'] : $defaults['layout'],
      '#attached' => array('css' => array(drupal_get_path('module', 'os_slideshow') . '/os_slideshow_layout_form.css')),
    );
    if ($this->new) {
      $form['layout']['#description'] .= ' ' . t('Note that the layout can be changed at a later date, but the aspect ratio (Standard/Widescreen) is permanent once selected.');
    }

    $form['display'] = array(
      '#type' => 'fieldset',
      '#title' => t('Display Options'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#weight' => 10,
    );

    $form['display']['timeout'] = array(
      '#type' => 'select',
      '#description' => t('Each slide will be displayed for this length of time.'),
      '#title' => t('Duration'),
      '#default_value' => $this->options['timeout'],
      '#options' => $this->_transition_speed_opts(1, 10, .5),
    );

    $form['display']['speed'] = array(
      '#type' => 'select',
      '#description' => t('Transitions between slides will take this long.'),
      '#title' => t('Transition Speed'),
      '#default_value' => $this->options['speed'],
      '#options' => $this->_transition_speed_opts(0, 1, .1),
    );

    $form['display']['random'] = array(
        '#type' => 'checkbox',
        '#title' => t('Random Order'),
        '#default_value' => $this->options['random'],
    );

    $form['#attached']['js'] = array(drupal_get_path('module', 'os_slideshow').'/plugins/os_slideshow_box.js',);

    if (empty($this->options['nodes'])) {
      $form['nodes'] = array(
        '#type' => 'markup',
        '#markup' => '<div class="messages warning">You haven\'t added any slides yet.  Put this widget in your layout and visit that page to add slides.</div>',
        '#weight' => 5,
      );
    }
    else {
      // Build a normal form.
      $form['nodes'] = array(
        '#type' => 'markup',
        '#tree' => TRUE,
        '#pre_render' => array('os_slideshow_draggable_table'),
        '#weight' => 5,
      );

      // Filter out dead nids.
      $nids = $this->_get_nids();

      $form['nodes']['#process'][] = 'os_slideshow_process_form_nodes';
      $form['nodes_list'] = array(
        '#type' => 'hidden',
        '#value' => $nids,
      );

      // Load slideshow_slide nodes.
      uasort($this->options['nodes'], 'element_sort');
      $nodes = node_load_multiple($nids);

      foreach ($this->options['nodes'] as $nid => $data) {
        if (!in_array($nid, $nids)) {
          continue;
        }

        $uri = $nodes[$nid]->field_image[$nodes[$nid]->language][0]['uri'];
        $img = theme('image_style', array('style_name' => 'thumbnail', 'path' => $uri, 'attributes' => array('style' => 'float: left; margin-right: 1em;')));
        $title = ($nodes[$nid]->status) ? '<strong>' . $nodes[$nid]->title . '</strong>' : '<em>' . $nodes[$nid]->title . ' (unpublished)</em>';

        // Edit link loads node edit with destination of this page. This page's
        // destination needs to be preserved. Nested destinations.
        $dest = (isset($_GET['destination'])) ? current_path() . '?destination=' . $_GET['destination'] : current_path();
        $edit_link = l('Edit Slide', "node/${nid}/edit", array('query' => array('destination' => $dest, 'widget' => $this->delta)));
        $remove_link =  '<a href="#" class="remove" title="Remove Slide">Remove</a>';
        $links = "<div>${title}<br />${edit_link} | ${remove_link}</div>";

        $form['nodes'][$nid] = array(
          'nid' => array(
            '#type' => 'hidden',
            '#default_value' => $nid,
          ),
          'text' => array(
            '#markup' => $img . $links,
          ),
          '#weight' => $data['weight'],
          'weight' => array(
            '#type' => 'textfield',
            '#default_value' => $data['weight'],
            '#size' => 3,
            '#attributes' => array('class' => array('field-weight')),
          ),
        );
      }
    }

    return $form;
  }

  public function render() {
    if (module_exists('vsite') && !vsite_get_vsite()) {
      return;
    }
    $block = parent::render();
    $options = $this->options + $this->options_defaults();
    $block['title'] = $block['subject'] = check_plain($this->title);

    // Show Add Slide link to admins.
    if (spaces_access_admin()) {
      $block['content'] = l('Add Slide', 'node/add/slideshow-slide', array(
        'attributes' => array('class' => array('add_new')),
        'query' => array('widget' => $this->delta, 'destination' => current_path()),
      ));
    }

    $vars = array_intersect_key($options, array_flip(array('nodes', 'timeout', 'speed', 'effect', 'layout', 'random')));
    $vars['box_delta'] = $this->delta;
    $block['content'] .= theme('os_slideshow_slideshow', $vars);
    return $block;
  }

  /**
   * @function _transition_speed_opts()
   *
   * Helper function for making for time selects.  All args are seconds.
   *
   * @returns array( $milliseconds => $seconds . 's')
   */
  private function _transition_speed_opts($min, $max, $increment) {
    $precision = explode('.', $increment);
    $decimals = (count($precision)>1) ? strlen($precision[1]) : 0;

    $return = array();
    for ($i = $min; $i <= $max; $i += $increment) {
      $return[$i*1000] = number_format($i, $decimals) . ' sec';
    }
    return $return;
  }

  // Filters out dead nids.
  private function _get_nids() {
    $nids = array_keys($this->options['nodes']);

    if ($nids) {
      $nids = db_select('node', 'n')
        ->fields('n', array('nid'))
        ->condition('n.nid', $nids, 'IN')
        ->condition('n.type', 'slideshow_slide')
        ->execute()
        ->fetchCol();
    }

    return $nids;
  }
}

/**
 * Helper function for building a render-able array of a draggable table.
 */
function os_slideshow_draggable_table($element) {
  // Render the form as a table
  $rows = array();
  uasort($element, 'element_sort');
  foreach (element_children($element) as $c) {
    $rows[] = array(
      'data' => array(
        drupal_render($element[$c]['nid']) . drupal_render($element[$c]['text']),
        drupal_render($element[$c]['weight']),
      ),
      'class' => ((string)$c != 'blank') ? array('draggable') : array(),
    );
  }
  $element['#headers'] = array();
  $element['#attributes'] = array('id' => 'slideshow-slides-list');
  $element['#rows'] = $rows;
  $element['#sticky'] = false;
  $element['#empty'] = true;
  //$element['#value'] = theme('table', array(), $rows);
  $element['#theme'] = 'table';
  drupal_add_tabledrag('slideshow-slides-list', 'order', 'sibling', 'field-weight');
  return $element;
}

/**
 * Ensures the value given is within acceptable ranges
 */
// function os_slideshow_accepted_range($element, &$form_state) {
//   $defaults = $form_state['box']->options_defaults();
//   if ($element['#value'] < $defaults['min_width'] || $element['#value'] > $defaults['max_width']) {
//     form_error($element, t('Slideshow width out of bounds: Width should be between %min and %max pixels.', array('%min'=>$defaults['min_width'], '%max'=>$defaults['max_width'])));
//   }
//   $element['#value'] = (int)$element['#value'];
// }

