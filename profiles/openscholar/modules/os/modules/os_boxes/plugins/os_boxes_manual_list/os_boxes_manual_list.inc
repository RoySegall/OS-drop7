<?php

class os_boxes_manual_list extends os_boxes_default {

  public function options_defaults() {
    return array(
      'nodes' => array(),
      'style' => 'titles',
    );
  }

  public function options_form(&$form_state) {
    $form = parent::options_form($form_state);

    $form['#attached']['js'] = array(
      drupal_get_path('module', 'os_boxes').'/plugins/os_boxes_manual_list/os_boxes_manual_list.js'
    );

    include_once (drupal_get_path('module', 'vsite') . '/includes/nodeautocomplete.inc');
    $form['add'] = array(
      '#type' => 'fieldset',
      '#title' => t('Add New Post'),
//      'node_to_add' => array(
//        '#type' => 'textfield',
//        '#description' => t('Start entering the title of a post and matching posts will appear.'),
//        '#autocomplete_path' => 'ctools/autocomplete/node',
//      	'#field_suffix' => '<input type="button" class="add_new" value="Add" />'
//      ),
      'node_to_add' => vsite_node_autocomplete_element() + array('#field_suffix' => '<input type="button" class="add_new" value="Add" />'),
    );

    // build a normal form
    $form['nodes'] = array(
      '#type' => 'markup',
      '#tree' => TRUE,
      '#pre_render' => array('os_boxes_manual_list_table'),
    );

    $nodes = &$form['nodes'];
    usort($this->options['nodes'], 'element_sort');

    $this->options['nodes']['blank'] = array('nid' => 0, 'title' => '__blank__', 'weight' => 2000000); // blank element for copying purposes
    foreach ($this->options['nodes'] as $k => $v) {
      $deleted = '';
      if (!($node = node_load($v['nid']))) {
        $deleted = ' &lt;Deleted! Please remove!&gt;';
      }
      $n = array(
        '#weight' => $v['weight'],
        'nid' => array(
          '#type' => 'hidden',
          '#default_value' => $v['nid'],
        ),
        'text' => array(
          '#type' => 'markup',
          '#markup' => '<span>'.$v['title'].$deleted.'</span> <a href="#" class="remove" title="Remove Post">Remove</a>',
        ),
        'title' => array(
          '#type' => 'hidden',
          '#default_value' => $v['title'],
        ),
        'weight' => array(
          '#type' => 'textfield',
          '#default_value' => $v['weight'],
          '#size' => 3,
          '#attributes' => array(
            'class' => (string)$k!='blank'?array('field-weight'):array(),
          )
        ),
      );
      $nodes[$k] = $n;
    }

    $form['style'] = array(
      '#type' => 'select',
      '#title' => t('Display Style'),
      '#options' => array(
        'full' => t('List of full posts'),
        'teasers' => t('List of teasers'),
        'titles' => t('List of titles')
      ),
      '#required' => TRUE,
      '#default_value' => $this->options['style']
    );

    $form['count'] = array(
      '#type' => 'hidden',
      '#default_value' => count($this->options['nodes'])-1,
      '#attributes' => array(
        'id' => 'edit-count',
      ),
      '#process' => array('os_boxes_manual_list_add_new_fields'),
    );
    return $form;
  }

  public function render() {
    if (module_exists('vsite') && !vsite_get_vsite()) {
      return;
    }
    $block = parent::render();
    $links = array();
    foreach ($this->options['nodes'] as $n) {
      if ($node = node_load($n['nid'])) {
        if ($this->options['style'] == 'teasers') {
          // Theme the nodes as a teaser
  
          //Node may not load if it has since been deleted
          $links[$n['weight']] = render(node_view($node, 'teaser'));
        }
        elseif ($this->options['style'] == 'full') {
          $node = node_load($n['nid']);
          $links[$n['weight']] = render(node_view($node, 'full'));
        }
        else {
          $l = array(
            'href' => 'node/'.$n['nid'],
            'title' => $n['title'],
          );
          $links[$n['weight']] = $l;
        }
      }
    }
    ksort($links);
    if(empty($links)) {
      $block['title'] = '';
      $block['subject'] = '';
      return $block;
    }
    if ($this->options['style'] == 'teasers' || $this->options['style'] == 'full') {
      $block['content'] = theme('item_list', array('items' => $links, 'attributes' => array('class' => array('featured-links'))));
    }
    else {
      $block['content'] = theme('links', array('links' => $links, 'attributes' => array('class' => array('featured-links'))));
    }
    return $block;
  }
}

function os_boxes_manual_list_table($element) {
  // render the form as a table
  $rows = array();
  uasort($element, 'element_sort');
  foreach (element_children($element) as $c) {
    $rows[] = array(
      'data' => array(
        drupal_render($element[$c]['nid']).drupal_render($element[$c]['text']).drupal_render($element[$c]['title']),
        drupal_render($element[$c]['weight']),
      ),
      'class' => (string)$c!='blank'?array('draggable'):array(),
    );
  }
  $element['#headers'] = array();
  $element['#attributes'] = array('id' => 'manual-nodes-list');
  $element['#rows'] = $rows;
  $element['#sticky'] = false;
  $element['#empty'] = true;
  //$element['#value'] = theme('table', array(), $rows, );
  $element['#theme'] = 'table';
  drupal_add_tabledrag('manual-nodes-list', 'order', 'sibling', 'field-weight');
  return $element;
}

function os_boxes_manual_list_add_new_fields($element, &$form_state, &$form) {
  for ($i=$element['#default_value']; $i < $element['#value']; $i++) {
    $form['options']['nodes'][$i] = array(
      '#attributes' => array('id' => $i),
      '#parents' => array('nodes', $i),
      '#array_parents' => array('options', 'nodes', $i),
      '#tree' => TRUE,
    );
    $form['options']['nodes'][$i] += $form['options']['nodes']['blank'];
    foreach ($form['options']['nodes'][$i] as $key => &$child) {
      if (strpos($key, '#') !== 0) {
        unset($child['#parents']);
        unset($child['#name']);
        unset($child['#value']);
      }
    }
    form_builder($form['form_id']['#value'], $form['options']['nodes'][$i], $form_state);
  }
  unset($form_state['values']['nodes']['blank']);

  // remove nids that aren't in the post
  if (is_array($form_state['values'])) {
    foreach ($form_state['values']['nodes'] as $k => $v) {
      if (!isset($form_state['input']['nodes'][$k]) || !isset($form_state['input']['nodes'][$k]['nid'])) {
        unset($form_state['values']['nodes'][$k]);
      }
    }
  }

  return $element;
}
