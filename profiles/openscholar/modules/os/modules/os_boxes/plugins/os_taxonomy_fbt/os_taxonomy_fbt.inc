<?php
// $Id$


/**
 * @author rbran100
 * @category boxes
 *
 * The class for filtering content by taxonomy.
 */
class os_taxonomy_fbt extends os_boxes_default {

  /**
   * Implements boxes_content::options_defaults().
   */
  public function options_defaults() {
    $options = parent::options_defaults();

    $options['vocabulary'] = FALSE;
    $options['bundles'] = array('--all--');
    $options['widget_type'] = 'list';
    $options['range'] = 10;
    $options['offset'] = 0;
    $options['show_empty_terms'] = FALSE;
    $options['show_term_descriptions'] = FALSE;
    $options['show_count'] = TRUE;
    $options['show_childs'] = TRUE;
    $options['add_childs'] = FALSE;
    $options['depth'] = 0;
    $options['behavior'] = 'contextual';
    $options['as_nav'] = FALSE;

    return $options;
  }

  /**
   * Implements boxes_content::options_form().
   */
  public function options_form(&$form_state) {
    $form = parent::options_form($form_state);

    ctools_include('dependent');
    ctools_add_js('dependent');

    $form = $this->form_elements();

    // Reset the keys.
    foreach (array_keys($form) as $setting) {
      $setting_value = !empty($this->options[$setting]) ? $this->options[$setting] : NULL;
      $form[$setting]['#default_value'] = $setting_value;
    }

    $form['advanced']['as_nav'] = array(
      '#type' => 'checkbox',
      '#default_value' => $this->options['as_nav'],
      '#title' => t('Display As Navigation'),
      '#description' => t('Check this to make this vocabulary display like a menu.'),
      '#return_value' => TRUE,
    );

    return $form;
  }

  /**
   * Returning the form for building the form and reset the form values with
   * $form keys.
   */
  public function form_elements() {
    $form = array();

    $form['vocabulary'] = array(
      '#type' => 'select',
      '#description' => t('Which vocabularies would you like to use to filter posts.'),
      '#title' => t('Vocabularies'),
      '#options' => self::get_all_vocabularies(),
      '#required' => TRUE,
    );

    $form['widget_type'] = array(
      '#type' => 'select',
      '#title' => t('Widget type'),
      '#description' => t('Select how to display the terms - in a select list or in html format'),
      '#options' => array(
        'list' => t('List'),
        'select' => t('Select list'),
      ),
      '#default_value' => $this->options['widget_type'] ? $this->options['widget_type'] : 'list',
    );

    $form['behavior'] = array(
      '#type' => 'select',
      '#title' => t('Post types'),
      '#options' => array(
        'contextual' => t("Determine for me"),
        '--all--' => t('All posts'),
        'select' => t('Select post types'),
      ),
      '#default_value' => $this->options['behavior'],
      '#description' => t('The post types that will included in the count. Determine for me will filter the content on the "current page".'),
    );

    $form['bundles'] = array(
      '#type' => 'select',
      '#title' => t('Select Post types'),
      '#options' => os_get_bundles(array(1,2)),
      '#description' => t('The post types that will be included in the count'),
      '#multiple' => TRUE,
      '#size' => count(os_get_bundles(array(1,2))) / 2,
      '#dependency' => array(
        'edit-behavior' => array('select'),
      ),
    );

    $form['range'] = array(
      '#type' => 'textfield',
      '#title' => t('Number of terms to display'),
      '#description' => t('Maximum number of terms to display.'),
      '#element_validate' => array('element_validate_integer_positive'),
    );

    $form['offset'] = array(
      '#type' => 'textfield',
      '#title' => t('Offset'),
      '#description' => t("The term location that the query start from."),      
    );

    $form['show_empty_terms'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show empty terms'),
      '#description' => t('Should terms be shown that do not have any posts tagged to them.'),
    );

    $form['show_term_descriptions'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show term descriptions'),
      '#description' => t('Show the description of the term if available under each term.'),
    );

    $form['show_childs'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show child terms'),
      '#description' => t('Control whether to child terms are shown with their parent term.'),
    );

    $form['depth'] = array(
      '#type' => 'select',
      '#title' => ('Taxonomy tree depth.'),
      '#description' => t('The maximum term level in the tree to count the tagged posts.'),
      '#options' => array(
        -1 => t("Show all children"),
        0 => t("Show only first level"),
        1 => t("2nd Level"),
        2 => t("3rd Level"),
        3 => t("4th Level"),
      ),
      '#process' => array('ctools_dependent_process'),
      '#dependency' => array(
        'edit-show-childs' => array(1),
      ),
    );

    $form['show_count'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show number of posts'),
      '#description' => t('Show number of posts tagged to a term next to the term.'),
    );

    return $form;
  }

  /**
   * Implements boxes_content::render().
   */
  public function render() {
    if (module_exists('vsite') && !vsite_get_vsite()) {
      return;
    }

    $block = parent::render();
    if (empty($this->options['vocabulary'])) {
      $this->options['vocabulary'] = current(array_keys(self::get_all_vocabularies()));

      if(empty($this->options['vocabulary'])){
        // There are no vocabularies defined in the VSite.
        return $block;
      }
    }
    ctools_include('layout', 'os');

    if ($this->options['behavior'] == '--all--') {
      $this->options['bundles'] = array();
    }
    else if (!empty($this->options['behavior']) && $this->options['behavior'] == 'contextual' && ($feature = os_get_active_feature())) {
      if (isset($feature->info['features']['node'])) {
        // Building a list of the bundles in two ways:
        // 1. Selected bundles from a list
        // 2. If the widget defined as a "Determine for me" set the bundles
        //    whcih related to the app.
        $paths = os_get_app_path();
        $menu = menu_get_item();

        $this->options['bundles'] = array();
        if ($menu['map'][0] == 'node') {
          $this->options['bundles'] = array($menu['map'][1]->type);
        }
        else {
          foreach ($paths as $bundle => $path) {
            if ($path == $menu['original_map'][0]) {
              $this->options['bundles'][] = $bundle;
            }
          }
        }
      }
    }

    if (is_array($this->options['vocabulary'])) {
      $t = array_filter($this->options['vocabulary']);
      $this->options['vocabulary'] = current($t);
    }

    if ($this->options['as_nav']) {
      $this->options['additional_classes'] = 'navigation';
    }

    $block['content'] = theme('os_taxonomy_vocabulary_item_list', array(
      'vid' => $this->options['vocabulary'],
      'options' => $this->options,
    ));

    return $block;
  }

  /**
   * Return the cache parameters for this box.
   */
  public function cache_info() {}

  /**
   * Get all the volcabularies id using the taxonomy terms.
   */
  private function get_all_vocabularies() {

    ctools_include('taxonomy', 'os');
    $taxonomy_vocabularies = os_get_vocabularies();
    $vocabularies = array();

    foreach ($taxonomy_vocabularies as $taxonomy_vocabulary) {
      $vocabularies[$taxonomy_vocabulary->vid] = $taxonomy_vocabulary->name;
    }

    return $vocabularies;
  }
}

