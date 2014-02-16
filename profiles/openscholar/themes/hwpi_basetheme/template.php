<?php

// Rebuild the theme data. Turn this off when in production.
//system_rebuild_theme_data();
//drupal_theme_rebuild();


/**
 * Preprocess variables for html.tpl.php
 */
function hwpi_basetheme_preprocess_html(&$vars) {

  $scripts = array(
    'matchMedia.js', // matchMedia polyfill for older browsers
    'eq.js',         // Equalheights script
    'eq-os.js',      // Call Equalheights for specific elements
    'scripts.js',    // General stuff, currently removes ui-helper-clearfix class from ui tabs
  );
  foreach ($scripts as $script) {
    // See load.inc in AT Core, load_subtheme_script() is a wrapper for drupal_add_js()
    load_subtheme_script('js/' . $script, 'hwpi_basetheme', 'header', $weight = NULL);
  }
}

/**
 * Adds mobile menu controls to menubar.
 */
function hwpi_basetheme_page_alter(&$page) {
  $page['header_second']['#sorted'] = false;
  $page['header_second']['mobile'] = array(
    '#theme' => 'links',
    '#attributes' => array(
      'class' => array('mobile-buttons'),
    ),
    '#weight' => 5000,
    '#links' => array(
      'mobi-main' => array(
        'href' => '#',
        'title' => '<span aria-hidden="true" class="icon-menu"></span>Menu',
        'external' => true,
        'html' => true,
        'attributes' => array(
          'data-target' => '#block-os-primary-menu',
        ),
      ),
      'mobi-util' => array(
        'href' => '#',
        'title' => '<span aria-hidden="true" class="icon-plus"></span><span class="move">Utility Menu</span>',
        'external' => true,
        'html' => true,
        'attributes' => array(
          'data-target' => '#block-os-quick-links, #block-os-secondary-menu, #header .os-custom-menu',
        ),
      ),
      'mobi-search' => array(
        'href' => '#',
        'title' => '<span aria-hidden="true" class="icon-search3"></span><span class="move">Search</span>',
        'external' => true,
        'html' => true,
        'attributes' => array(
          'data-target' => '#block-os-search-db-site-search, #block-os-search-solr-site-search',
        )
      )
    )
  );

  if (context_isset('context', 'os_public') && variable_get('enable_responsive', false)) {
    $path = drupal_get_path('theme', 'hwpi_basetheme').'/css/';
    drupal_add_css($path.'responsive.base.css');
    drupal_add_css($path.'responsive.layout.css');
    drupal_add_css($path.'responsive.nav.css');
    drupal_add_css($path.'responsive.slideshow.css');
    drupal_add_css($path.'responsive.widgets.css');

    $theme = $GLOBALS['theme'];
    $theme_path = drupal_get_path('theme', $theme).'/css/';
    drupal_add_css($theme_path.'responsive.'.str_replace('hwpi_', '', $theme).'.css');
  }
}

/**
 * Preprocess variables for comment.tpl.php
 */
function hwpi_basetheme_preprocess_node(&$vars) {
  if ($vars['type'] != 'person') {
    return;
  }

  if (!empty($vars['field_person_photo'])) {
    $vars['classes_array'][] = 'with-person-photo';
  }
  else {
    // If node is in teaser view mode, load a default image. If node is displayed
    // in "List of posts" widget or in full display mode, load a bigger default image.
    if (in_array($vars['view_mode'], array('teaser'))) {
      // Check if profile is in a widget.
      if (!empty($vars['sv_list'])) {
        // Use default image.
        $path = variable_get('os_person_default_image', drupal_get_path('theme', 'hwpi_basetheme') . '/images/person-default-image.png');
        $image = '<div class="field-name-field-person-photo">' . theme('image',  array('path' => $path)) . '</div>';
        $vars['content']['field_person_photo'][0] = array('#markup' => $image);
      }
      // Profile is not in a widget. Check if default image is disabled. If it is, print an empty div.
      elseif (variable_get('os_profiles_disable_default_image', FALSE)){
        $vars['content']['field_person_photo'][0] = array('#markup' => '<div class="no-default-image"></div>');
      }
      else {
        if ($custom_default_image = variable_get('os_profiles_default_image_file', 0)) {
          // Use custom default image.
          $image_file = file_load($custom_default_image);
          $path = $image_file->uri;
          $options = array(
            'path' => $path,
            'style_name' => 'profile_thumbnail',
          );
          $image = '<div class="field-name-field-person-photo">' . theme('image_style',  $options) . '</div>';
        }
        else {
          // Use default image.
          $path = variable_get('os_person_default_image', drupal_get_path('theme', 'hwpi_basetheme') . '/images/person-default-image.png');
          $image = '<div class="field-name-field-person-photo">' . theme('image',  array('path' => $path)) . '</div>';
        }
        $vars['content']['field_person_photo'][0] = array('#markup' => $image);
      }
    }
    elseif ((!empty($vars['os_sv_list_box']) && $vars['os_sv_list_box']) || $vars['view_mode'] == 'full') {
      $path = variable_get('os_person_default_image_big', drupal_get_path('theme', 'hwpi_basetheme') . '/images/person-default-image-big.png');
      $image = '<div class="field-name-field-person-photo">' . theme('image',  array('path' => $path)) . '</div>';
      // Big image.
      $vars['content']['pic_bio']['field_person_photo'][0] = array('#markup' => $image);

      // If 'body' is empty make sure image is displayed.
      if (empty($vars['body'])) {
        $vars['content']['pic_bio']['#access'] = TRUE;
      }
    }
    elseif ($vars['view_mode'] == 'sidebar_teaser') {
      // Check if profile is in a widget.
      if (!empty($vars['sv_list'])) {
        // Use default image.
        $path = variable_get('os_person_default_image', drupal_get_path('theme', 'hwpi_basetheme') . '/images/person-default-image.png');
        $image = '<div class="field-name-field-person-photo">' . theme('image',  array('path' => $path)) . '</div>';
        $vars['content']['pic_bio']['field_person_photo'][0] = array('#markup' => $image);
      }
      // Profile is not in a widget. Check if default image is disabled. If it is, print an empty div.
      elseif (variable_get('os_profiles_disable_default_image', FALSE)){
        $vars['content']['pic_bio']['field_person_photo'][0] = array('#markup' => '<div class="no-default-image"></div>');
      }
      else {
        if ($custom_default_image = variable_get('os_profiles_default_image_file', 0)) {
          // Use custom default image.
          $image_file = file_load($custom_default_image);
          $path = $image_file->uri;
          $options = array(
            'path' => $path,
            'style_name' => 'profile_thumbnail',
          );
          $image = '<div class="field-name-field-person-photo">' . theme('image_style',  $options) . '</div>';
        }
        else {
          // Use default image.
          $path = variable_get('os_person_default_image', drupal_get_path('theme', 'hwpi_basetheme') . '/images/person-default-image.png');
          $image = '<div class="field-name-field-person-photo">' . theme('image',  array('path' => $path)) . '</div>';
        }
        $vars['content']['pic_bio']['field_person_photo'][0] = array('#markup' => $image);
      }
      // Make sure image will be displayed.
      $vars['content']['pic_bio']['#access'] = TRUE;
    }
  }
}

/**
 * Process variables for comment.tpl.php
 */
function hwpi_basetheme_process_node(&$vars) {
  // Event persons, change title markup to h1
  if ($vars['type'] == 'person') {
    if ($vars['view_mode'] == 'title') {
      $vars['title_prefix']['#suffix'] = '<h1 class="node-title">' . l($vars['title'], 'node/' . $vars['nid']) . '</h1>';
      $vars['title'] = NULL;
    }
    elseif (!$vars['teaser'] && $vars['view_mode'] != 'sidebar_teaser') {
      $vars['title_prefix']['#suffix'] = '<h1 class="node-title">' . $vars['title'] . '</h1>';
      $vars['title'] = NULL;
      
      if ($vars['view_mode'] == 'slide_teaser') {
        $vars['title_prefix']['#suffix'] = '<div class="toggle">' . $vars['title_prefix']['#suffix'] . '</div>';
      }
    }
  }
}

/**
 * Implements hook_field_display_ENTITY_TYPE_alter().
 */
function hwpi_basetheme_field_display_node_alter(&$display, $context) {
  if ($context['entity']->type == 'event' && $context['instance']['field_name'] == 'field_date') {
    if (($context['view_mode'] != 'full') || (isset($context['entity']->os_sv_list_box) && $context['entity']->os_sv_list_box)) {

      if (isset($context['entity']->field_date[LANGUAGE_NONE][0]['value2']) &&
          (strtotime($context['entity']->field_date[LANGUAGE_NONE][0]['value2']) - strtotime($context['entity']->field_date[LANGUAGE_NONE][0]['value']) > 24*60*60)) {
        return; //event is more than one day long - keep both dates visible
      }

      //hide the date - it's already visible in the shield
      $display['settings']['format_type'] = 'os_time';
    }
  }
}

/**
 * Alter the results of node_view().
 */
function hwpi_basetheme_node_view_alter(&$build) {
  // Persons, heavily modify the output to match the HC designs
  if ($build['#node']->type == 'person') {

    if ($build['#view_mode'] == 'sidebar_teaser') {
      $build['pic_bio']['#prefix'] = '<div class="pic-bio clearfix people-sidebar-teaser">';
    }
    else {
      $build['pic_bio']['#prefix'] = '<div class="pic-bio clearfix">';
    }
    $build['pic_bio']['#suffix'] = '</div>';
    $build['pic_bio']['#weight'] = -9;

    if (isset($build['body'])) {
      $build['body']['#label_display'] = 'hidden';
      $build['pic_bio']['body'] = $build['body'];
      unset($build['body']);
    }

    //join titles
    $title_field = &$build['field_professional_title'];
    if ($title_field) {
      $keys = array_filter(array_keys($title_field), 'is_numeric');
      foreach ($keys as $key) {
        $titles[] = $title_field[$key]['#markup'];
        unset($title_field[$key]);
      }
      $glue = ($build['#view_mode'] == 'sidebar_teaser') ? ', ' : "<br />\n";
      $title_field[0] = array('#markup' => implode($glue, $titles));
    }

    // We dont want the other fields on teasers
    if (in_array($build['#view_mode'], array('teaser', 'slide_teaser','no_image_teaser'))) {

      //move title, website. body
      $build['pic_bio']['body']['#weight'] = 5;
      foreach (array(0=>'field_professional_title', 10=>'field_website') as $weight => $field) {
        if (isset($build[$field])) {
          $build['pic_bio'][$field] = $build[$field];
          $build['pic_bio'][$field]['#weight'] = $weight;
          unset($build[$field]);
        }
      }

      //hide the rest
      foreach (array('field_address') as $field) {
        if (isset($build[$field])) {
          unset($build[$field]);
        }
      }

      if (isset($build['field_email'])) {
        $email_plain = $build['field_email'][0]['#markup'];
        $build['field_email'][0]['#markup'] = '<a href="mailto:' . $email_plain . '">' . $email_plain . '</a>';
      }

      // Newlines after website.
      if (isset($build['pic_bio']['field_website'])) {
        foreach (array_filter(array_keys($build['pic_bio']['field_website']), 'is_numeric') as $delta) {
          $item = $build['pic_bio']['field_website']['#items'][$delta];
          $build['pic_bio']['field_website'][$delta]['#markup'] = l($item['title'], $item['url'], $item) . '<br />';
        }
      }

      unset($build['links']['node']);

      return;
    }

    // Professional titles
    if (isset($build['field_professional_title'])) {
      $build['field_professional_title']['#label_display'] = 'hidden';
      $build['field_professional_title']['#weight'] = -10;
    }

    if (isset($build['field_person_photo'])) {
      $build['field_person_photo']['#label_display'] = 'hidden';
      $build['pic_bio']['field_person_photo'] = $build['field_person_photo'];
      unset($build['field_person_photo']);
    }

    $children = element_children($build['pic_bio']);
    if (empty($children)) {
      $build['pic_bio']['#access'] = false;
    }

    // Note that Contact and Website details will print wrappers and titles regardless of any field content.
    // This is kind of deliberate to avoid having to handle the complexity of dealing with the layout or
    // setting messages etc.

    $block_zebra = 0;

    // Contact Details
    if ($build['#view_mode'] != 'sidebar_teaser') {
      $build['contact_details']['#prefix'] = '<div class="block contact-details '.(($block_zebra++ % 2)?'even':'odd').'"><div class="block-inner"><h2 class="block-title">Contact Information</h2>';
      $build['contact_details']['#suffix'] = '</div></div>';
      $build['contact_details']['#weight'] = -8;

      // Contact Details > address
      if (isset($build['field_address'])) {
        $build['field_address']['#label_display'] = 'hidden';
        $build['contact_details']['field_address'] = $build['field_address'];
        $build['contact_details']['field_address'][0]['#markup'] = str_replace("\n", '<br>', $build['contact_details']['field_address'][0]['#markup']);
        unset($build['field_address']);
      }
      // Contact Details > email
      if (isset($build['field_email'])) {
        $build['field_email']['#label_display'] = 'inline';
        $email_plain = mb_strtolower($build['field_email'][0]['#markup']);
        if ($email_plain) {

          $build['field_email'][0]['#markup'] = l($email_plain, 'mailto:'.$email_plain, array('absolute'=>TRUE));
        }
        $build['contact_details']['field_email'] = $build['field_email'];
        $build['contact_details']['field_email']['#weight'] = -50;
        unset($build['field_email']);
      }
      // Contact Details > phone
      if (isset($build['field_phone'])) {
        $build['field_phone']['#label_display'] = 'hidden';
        $phone_plain = $build['field_phone'][0]['#markup'];
        if ($phone_plain) {
          $build['field_phone'][0]['#markup'] = t('p: ') . $phone_plain;
        }
        $build['contact_details']['field_phone'] = $build['field_phone'];
        $build['contact_details']['field_phone']['#weight'] = 50;
        unset($build['field_phone']);
      }

      // Websites
      if (isset($build['field_website'])) {
        $build['website_details']['#prefix'] = '<div class="block website-details '.(($block_zebra++ % 2)?'even':'odd').'"><div class="block-inner"><h2 class="block-title">Websites</h2>';
        $build['website_details']['#suffix'] = '</div></div>';
        $build['website_details']['#weight'] = -7;
        $build['field_website']['#label_display'] = 'hidden';
        $build['website_details']['field_website'] = $build['field_website'];
        unset($build['field_website']);
      }

      //Don't show an empty contact details section.
      if (!element_children($build['contact_details'])) {
        unset($build['contact_details']);
      }
    }

    if (isset($build['og_vocabulary'])) {
      $terms = array();
      foreach ($build['og_vocabulary']['#items'] as $i) {
        if (isset($i['target_id'])) {
          $terms[] = $i['target_id'];
        }
        else {
          $terms[] = $i;
        }
      }

      $terms = taxonomy_term_load_multiple($terms);
      $ordered_terms = array();

      foreach ($terms as $term) {
        $vocabulary = taxonomy_vocabulary_load($term->vid);
        $ordered_terms[] = array(
          'term' => $term,
          'weight' => $vocabulary->weight,
          'vid' => $vocabulary->vid,
        );
      }
      uasort($ordered_terms, 'og_vocab_sort_weight');
      foreach ($ordered_terms as $info) {
        $t = $info['term'];
        $v = taxonomy_vocabulary_load($t->vid);

        if (!isset($build[$v->machine_name])) {
          $m = $v->machine_name;
          $build[$m] = array(
            '#type' => 'container',
            '#weight' => $block_zebra,
            '#attributes' => array(
              'class' => array(
                'block',
                $m,
                (($block_zebra++ % 2)?'even':'odd')
              )
            ),
            'inner' => array(
              '#type' => 'container',
              '#attributes' => array(
                'class' => array('block-inner'),
              ),
              'title' => array(
                '#markup' => '<h2 class="block-title">'.$v->name.'</h2>',
              )
            ),
          );
        }

        $term_uri = entity_uri('taxonomy_term', $t);
        $build[$v->machine_name]['inner'][$t->tid] = array(
          '#prefix' => '<div>',
          '#suffix' => '</div>',
          '#theme' => 'link',
          '#path' => $term_uri['path'],
          '#text' => $t->name,
          '#options' => array('attributes' => array(), 'html' => false),
        );
      }

      unset($build['og_vocabulary']);
    }
  }
}


/**
 * Preprocess variables for comment.tpl.php
 */
function hwpi_basetheme_preprocess_comment(&$vars) {
  if($vars['new']) {
    $vars['title'] = $vars['title'] . '<em class="new">' . $vars['new'] . '</em>';
    $vars['new'] = '';
  }
}


/**
 * Returns HTML for a menu link and submenu.
 *
 * Adaptivetheme overrides this to insert extra classes including a depth
 * class and a menu id class. It can also wrap menu items in span elements.
 *
 * @param $vars
 *   An associative array containing:
 *   - element: Structured array data for a menu link.
 */
function hwpi_basetheme_menu_link(array $vars) {
  $element = $vars['element'];
  $sub_menu = '';

  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }

  if (!empty($element['#original_link'])) {
    if (!empty($element['#original_link']['depth'])) {
      $element['#attributes']['class'][] = 'menu-depth-' . $element['#original_link']['depth'];
    }
    if (!empty($element['#original_link']['mlid'])) {
      $element['#attributes']['class'][] = 'menu-item-' . $element['#original_link']['mlid'];
    }
  }

  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>";
}


/**
 * Returns HTML for a set of links.
 *
 * @param $vars
 *   An associative array containing:
 *   - links: An associative array of links to be themed. The key for each link
 *     is used as its CSS class. Each link should be itself an array, with the
 *     following elements:
 *     - title: The link text.
 *     - href: The link URL. If omitted, the 'title' is shown as a plain text
 *       item in the links list.
 *     - html: (optional) Whether or not 'title' is HTML. If set, the title
 *       will not be passed through check_plain().
 *     - attributes: (optional) Attributes for the anchor, or for the <span> tag
 *       used in its place if no 'href' is supplied. If element 'class' is
 *       included, it must be an array of one or more class names.
 *     If the 'href' element is supplied, the entire link array is passed to l()
 *     as its $options parameter.
 *   - attributes: A keyed array of attributes for the UL containing the
 *     list of links.
 *   - heading: (optional) A heading to precede the links. May be an associative
 *     array or a string. If it's an array, it can have the following elements:
 *     - text: The heading text.
 *     - level: The heading level (e.g. 'h2', 'h3').
 *     - class: (optional) An array of the CSS classes for the heading.
 *     When using a string it will be used as the text of the heading and the
 *     level will default to 'h2'. Headings should be used on navigation menus
 *     and any list of links that consistently appears on multiple pages. To
 *     make the heading invisible use the 'element-invisible' CSS class. Do not
 *     use 'display:none', which removes it from screen-readers and assistive
 *     technology. Headings allow screen-reader and keyboard only users to
 *     navigate to or skip the links. See
 *     http://juicystudio.com/article/screen-readers-display-none.php and
 *     http://www.w3.org/TR/WCAG-TECHS/H42.html for more information.
 */
function hwpi_basetheme_links($vars) {
  $links = $vars['links'];
  $attributes = $vars['attributes'];
  $heading = $vars['heading'];
  global $language_url;
  $output = '';

  if (count($links) > 0) {
    $output = '';

    if (!empty($heading)) {
      if (is_string($heading)) {
        $heading = array(
          'text' => $heading,
          'level' => 'h2',
        );
      }
      $output .= '<' . $heading['level'];
      if (!empty($heading['class'])) {
        $output .= drupal_attributes(array('class' => $heading['class']));
      }
      $output .= '>' . check_plain($heading['text']) . '</' . $heading['level'] . '>';
    }

    // Count links to use later for setting classes on the ul wrapper and on
    // each link
    $num_links = count($links);
    $i = 1;

    // Add a class telling us how many links there are, we need to check if
    // $attributes['class'] is an array because toolbar is converting this to
    // a string, if we don't check we get a fatal error. This class is added
    // to aid in potential cross browser issues with the full width ui.tabs
    if (isset($attributes['class']) && is_array($attributes['class'])) {
      $attributes['class'][] = 'num-links-' . $num_links;
    }
    $output .= '<ul' . drupal_attributes($attributes) . '>';

    foreach ($links as $key => $link) {
      // Add classes to make theming the ui.tabs much easier/possible
      $class = array();
      $class[] = 'link-count-' . $key;
      if ($i == 1) {
        $class[] = 'first';
      }
      if ($i == $num_links) {
        $class[] = 'last';
      }
      if (!empty($class)) {
        $output .= '<li' . drupal_attributes(array('class' => $class)) . '>';
      }
      else {
        $output .= '<li>';
      }
      if (isset($link['href'])) {
        $output .= l($link['title'], $link['href'], $link);
      }
      elseif (!empty($link['title'])) {
        if (empty($link['html'])) {
          $link['title'] = check_plain($link['title']);
        }
        $span_attributes = '';
        if (isset($link['attributes'])) {
          $span_attributes = drupal_attributes($link['attributes']);
        }
        $output .= '<span' . $span_attributes . '>' . $link['title'] . '</span>';
      }

      $i++;
      $output .= "</li>";
    }

    $output .= '</ul>';
  }

  return $output;
}

/**
 * Returns HTML for status and/or error messages, grouped by type.
 *
 * Adaptivetheme adds a div wrapper with CSS id.
 *
 * An invisible heading identifies the messages for assistive technology.
 * Sighted users see a colored box. See http://www.w3.org/TR/WCAG-TECHS/H69.html
 * for info.
 *
 * @param $vars
 *   An associative array containing:
 *   - display: (optional) Set to 'status' or 'error' to display only messages
 *     of that type.
 */
function hwpi_basetheme_status_messages($vars) {
  $display = $vars['display'];
  $output = '';
  $allowed_html_elements = '<'. implode('><', variable_get('html_title_allowed_elements', array('em', 'sub', 'sup'))) . '>';

  $status_heading = array(
    'status' => t('Status update'),
    'error' => t('Error'),
    'warning' => t('Warning'),
  );
  foreach (drupal_get_messages($display) as $type => $messages) {
    $output .= '<div class="messages ' . $type . '"><div class="message-inner"><div class="message-wrapper">';
    if (!empty($status_heading[$type])) {
      $output .= '<h2>' . $status_heading[$type] . "</h2>";
    }
    if (count($messages) > 1) {
      $output .= " <ul>";
      foreach ($messages as $message) {
        if (strpos($message, 'Biblio') === 0) {
          // Allow some tags in messages about a Biblio.
          $output .= '  <li>' . strip_tags(html_entity_decode($message), $allowed_html_elements) . "</li>";
        }
        else {
          $output .= '  <li>' . $message . "</li>";
        }
      }
      $output .= " </ul>";
    }
    elseif (strpos($messages[0], 'Biblio') === 0 || strpos($messages[0], 'Publication') === 0) {
      // Allow some tags in messages about a Biblio.
      $output .= strip_tags(html_entity_decode($messages[0]), $allowed_html_elements);
    }
    else {
      $output .= $messages[0];
    }
    $output .= "</div></div></div>";
  }
  return $output;
}

function hwpi_basetheme_date_formatter_pre_view_alter(&$entity, $vars) {
  if ($entity->type != 'event') {
    return;
  }

  // Only display the start time for this particular instance of a repeat event.
  if (!$entity->view = views_get_current_view()) {
    return;
  }



  // Don't remove the field date when exporting the calendar. This the unique
  // identifier of Google calendar.
  if ($entity->view->plugin_name == 'date_ical') {
    return;
  }

  if (isset($entity->view) && isset($entity->view->row_index) && isset($entity->view->result[$entity->view->row_index])) {
    $result = $entity->view->result[$entity->view->row_index];
    $field = 'field_data_field_date_field_date_value';
    $delta = -1;
    foreach ($entity->field_date[LANGUAGE_NONE] as $d => $r) {
      if ($r['value'] == $result->$field) {
        $delta = $d;
        break;
      }
    }
    $entity->date_id = 'node.'.$entity->nid.'.field_date.'.$delta;
  }
  else {
    $entity->active_date = $vars['items'][0];
  }
}

/**
 * Implements template_process_HOOK() for theme_pager_link().
 */
function hwpi_basetheme_process_pager_link($variables) {
  // Adds an HTML head link for rel='prev' or rel='next' for pager links.
  module_load_include('inc', 'os', 'includes/pager');
  _os_pager_add_html_head_link($variables);
}
