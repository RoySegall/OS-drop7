<?php
// $Id$

function os_publications_overview() {
  $args = func_get_args();

  if (count($args) == 0) {
    // get default types the user has selected
    $defaults = variable_get('os_publications_filter_publication_types', array());

    //Filter out bad data
    unset($defaults[-1]);

    if (count(array_filter($defaults))) {
      $args = array('type', array_filter($defaults));
    }
  }

//   $ckey = _os_publications_cache_key($args);
//   if ($cache = cache_get($ckey, 'cache_biblio_lists')) {
//     return $cache->data;
//   }

  module_load_include('inc', 'biblio', 'includes/biblio.pages');
  $output = call_user_func_array('biblio_page', $args);

  // remove the filter status message
  unset($output['biblio_page']['header']['filter_status']);

  // remove the sorting option
  unset($output['biblio_page']['header']['sort_links']);

  // remove the alphabetic filtering
  unset($output['biblio_page']['header']['alpha_line']);

  // handle caching
  //cache_set($ckey, $output, 'cache_biblio_lists');

  // change the page title to match the menu entry
  ctools_include('menu', 'os');
  $menu_item = os_menu_load_link_path($_GET['q']);
  drupal_set_title($menu_item['title']);

  return $output;
}

function _os_publications_cache_key($args) {
  $info = array(
    'func_args' => $args,
    'uri' => drupal_parse_url(request_uri()),
  );
  module_load_include('inc', 'biblio', 'includes/biblio.pages');
  $arg_list = biblio_arg_handler($info);

  $key = array();
  $key[] = 'biblio';

  if (module_exists('spaces') && $space = spaces_get_space()) {
    $key[] = 'space';
    $key[] = $space->id;
  }

  $has_arg = false;
  if (isset($arg_list['f'])) {
    $has_arg = true;
    foreach ($arg_list['f'] as $l => $d) {
      if (is_array($d)) {
        foreach ($d as $v) {
          $key[] = $l;
          $key[] = $v;
        }
      }
      else {
        $key[] = $l;
        $key[] = $d;
      }
    }
  }

  if (isset($arg_list['s'])) {
    $has_arg = true;
    $key[] = 'sort';
    $key[] = $arg_list['s'];
  }

  if (isset($arg_list['o'])) {
    $has_arg = true;
    $key[] = 'order';
    $key[] = $arg_list['o'];
  }

  if (!$has_arg) {
    $key[] = 'args';
    $key[] = 'no';
  }

  if (isset($_GET['page'])) {
    $key[] = 'page';
    $key[] = $_GET['page'];
  }

  return implode(':', $key);
}

function os_publications_export($format = "tagged", $nid = NULL, $popup = FALSE) {
  module_load_include('inc', 'biblio', 'includes/biblio.import.export');

  $title = 'publications';
  if ($nid !== NULL) {
    $node  = node_load($nid);
    $title = str_replace(' ', '_', $node->title);
    $title = substr($title, 0, 8);
  }
  elseif (empty($_SESSION['last_biblio_query'])) {
    // Biblio uses this session value, if this is an anon user that has no session (or a cli user) lets set this up for them
    $args = array();
    // get default types the user has selected
    $defaults = variable_get('os_publications_default_types', array());
    if (count($defaults)) {
      $args = array('type', $defaults);
    }
    // Setup the default query
    module_load_include('inc', 'biblio', 'includes/biblio.pages');
    biblio_build_query($args);
  }

  ob_start();
  $output = biblio_export($format, $nid, $popup);
  if (empty($output)) {
    // the export didn't return anything, which means it output directly to the browser
    $output = ob_get_clean();

    // handle for spaces
    if (module_exists('spaces') && $space = spaces_get_space()) {
      $title = $space->group->purl . '-' . $title;
    }

    $header = drupal_get_http_header('Content-Disposition');

    $match = array();
    preg_match('!filename="([^"]+)"!', $header, $match);
    $filename = str_replace(array('Drupal-Biblio', 'Biblio'), $title, $match[1]);
    $header_new = preg_replace('!filename="([^"]+)"!', 'filename="' . $filename . '"', $header);

    drupal_add_http_header('Content-Disposition', $header_new);
    echo $output;
  }
  else {
    ob_end_clean();
    return $output;
  }
}

function os_publications_settings() {
  $style_name = biblio_get_style();

  $form['left'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('column', 'column-left'),
    ),
  );
  $form['right'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('column', 'column-right'),
    ),
  );
  $style = module_exists('biblio_citeproc') ? 'biblio_citeproc_style' : 'biblio_style';
  // Attach extra HTML to the citation array to allow for a popup box that will display an example of the citation format.
  $biblio_styles = biblio_get_styles();
  if(isset($biblio_styles) && is_array($biblio_styles)) {
    $biblio_styles_hover = array();
    $counter = 0;
    foreach($biblio_styles as $styles => $name) {
      $counter ++;
      // Setup the new citation options to be wrapped for a popup.
      $cite_example_link = '<a href="#" class="cite-pop" data-popbox="pop'.$counter.'">' . t('@link_name', array('@link_name' => $name)) . '</a>';
      // Setup the h2.
      $cite_example_title = '<h2>' . t('@csl_title', array('@csl_title' => $name)) . '</h2>';
      // Setup the citation exmaple for the popup.
      $citation_example = _os_publications_build_citation_example($styles); //'test text';
      $cite_example_text = '<p>' . t('!cite_text', array('!cite_text' => $citation_example)) . '</p>';
      // Concat it all together.
      $cite_example_output = $cite_example_link . '<div id="pop'.$counter.'" class="citebox">' . $cite_example_title . $cite_example_text . '</div>';
      $biblio_styles_hover[$styles] = $cite_example_output;
    }
  }
  $form['left'][$style] = array(
    '#type' => 'radios',
    '#title' => t('Select your preferred bibliographic format'),
    //'#description' => t('This alters the bibliographic format of your publications.'),
    '#default_value' => biblio_get_style(),
    '#options' => $biblio_styles_hover,
    '#attached' => array(
      'css' => array(
        drupal_get_path('module', 'os_publications') . '/misc/os_publications.css',
      ),
      'js' => array(
        drupal_get_path('module', 'os_publications') . '/misc/os_publications_csl_hover.js',
      )
    ),
  );

  $form['right']['biblio_export_links'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Select which export formats should accompany each bibliographic record'),
    '#default_value' => variable_get('biblio_export_links', array('tagged', 'xml', 'bibtex')),
    '#options' => array(
      'tagged' => t('EndNote Tagged'),
      'xml' => t('EndNote XML'),
      'bibtex' => t('BibTex'),
    ),
    '#description' => t('Each selected format will appear in its own export link.'),
  );

  //citation distribute plugins
  /*
   $form['right']['citation_distribute_autoflags'] = array(
     '#title' => t('Automatic Node Flagging'),
     '#type' => 'checkboxes',
     '#description' => t('New publications will automatically be flagged for distribution to the selected services.'),
     '#default_value' => variable_get('citation_distribute_autoflags', array()),
     '#options' => array(),
   );
   foreach (_citation_distribute_plugins() as $plugin) {
     if (isset($plugin['title'])) {
       $form['citation_distribute_autoflags']['#options'] += array($plugin['handler']['class'] => $plugin['title']);
     }
   }*/

  $form['right']['os_publications_note_in_teaser'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show the "note" content in teaser?'),
    //'#description' => t('This alters the bibliographic format of your publications.'),
    '#default_value' => variable_get('os_publications_note_in_teaser', FALSE),
    '#description' => t('If this is checked and you add a note to a publication then it will show as part of a publications teaser.'),
  );

  $form['left']['biblio_sort'] = array(
    '#type' => 'radios',
    '#title' => t('By default, sort publications by which category'),
    '#default_value' => variable_get('biblio_sort', 'year'),
    '#options' => array('author' => t('Author'), 'title' => t('Title'), 'type' => t('Type'), 'year' => t('Year')),
  );

  $form['left']['biblio_order'] = array(
    '#type' => 'radios',
    '#title' => t('Select default order of the sort category'),
    '#default_value' => variable_get('biblio_order', 'DESC'),
    '#options' => array('DESC' => t('Descending'), 'ASC' => t('Ascending')),
  );

  $result = db_query('SELECT t.* FROM {biblio_types} as t WHERE tid > -1 AND visible = 1');
  foreach ($result as $option) {
    $results[$option->tid] = $option->name;
  }
  asort($results);

  $form['right']['os_publications_filter_publication_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Show only publications of type'),
    '#default_value' => variable_get('os_publications_filter_publication_types', array_keys($results)),
    '#options' => $results,
    '#description' => t('The main list of publications on your publications page will list the types selected here.'),
    '#attributes' => array('class' => array('form-checkboxes-scrolling')),
  );

  //Should urls in citations be shortened?
/*  $form['scholar_publications'] = array(
  '#type' => 'fieldset',
  );
*/
  $form['right']['os_publications_shorten_citations'] = array(
    '#type' => 'checkbox',
    '#title' => t('Short URLs in citations'),
    '#description' => t('When this is checked, a shortened URL will be included in the citation.'),
    '#default_value' => variable_get('os_publications_shorten_citations'),
  );

  return system_settings_form($form);
}

function os_publications_reset(&$form, &$form_state) {
  $form['help'] = array(
    '#markup' => t('Select tables to reset:'),
  );

  $form['biblio_field_type'] = array(
    '#type' => 'checkbox',
    '#title' => t('Field Settings'),
    '#description' => t('Will update standard publication types to our defaults. Will not affect publication types you have added.'),
  );

  $form['biblio_contributor_type'] = array(
    '#type' => 'checkbox',
    '#title' => t('Contributor Settings'),
    '#description' => t('Will completely replace all Contributor settings.'),
  );

  $form['actions'] = array(
    '#type' => 'actions',
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Go'),
    )
  );

  $form['#submit'][] = 'os_publications_reset_submit';
}

function os_publications_reset_submit($form, $form_state) {
  //dpm($form_state['values']);
}

/**
 * Return a pre-built node for an example citation.
 */
function _os_publications_get_citation_example() {

  // Basic author listing.
  $contributors = array(
    0 => array(
      'lastname' => 'Doe',
      'firstname' => 'John',
      'initials' => 'A',
      'auth_category' => 1,
      'cid' => -1),
    1 => array(
      'lastname' => 'Smith',
      'firstname' => 'Richard',
      'initials' => 'B',
      'auth_category' => 1,
      'cid' => -2),
    3 => array(
      'lastname' => 'Editor',
      'firstname' => 'Edwin',
      'initials' => 'Z',
      'auth_category' => 2,
      'cid' => -3),
  );

  // 10+ author example to display the different ways "et al" works.
  $contributors_etall = array(
    0 => array( 'lastname' => 'Doe', 'firstname' => 'John', 'initials' => 'A', 'auth_category' => 1, 'cid' => -1),
    1 => array( 'lastname' => 'Smith', 'firstname' => 'Richard', 'initials' => 'B', 'auth_category' => 1, 'cid' => -2),
    3 => array( 'lastname' => 'Rodgers', 'firstname' => 'Edwin', 'initials' => 'Z', 'auth_category' => 1, 'cid' => -3),
    4 => array( 'lastname' => 'Howard', 'firstname' => 'Ron', 'initials' => 'Z', 'auth_category' => 1, 'cid' => -4),
    5 => array( 'lastname' => 'Rodgers', 'firstname' => 'Jill', 'initials' => 'Z', 'auth_category' => 1, 'cid' => -5),
    6 => array( 'lastname' => "O'Donnell", 'firstname' => 'Frank', 'initials' => 'Z', 'auth_category' => 1, 'cid' => -6),
    7 => array( 'lastname' => 'McQuiad', 'firstname' => 'Robert', 'initials' => 'Z', 'auth_category' => 1, 'cid' => -7),
    8 => array( 'lastname' => 'Smith', 'firstname' => 'Jane', 'initials' => 'Z', 'auth_category' => 1, 'cid' => -8),
    9 => array( 'lastname' => 'Ortiz', 'firstname' => 'Oscar', 'initials' => 'Z', 'auth_category' => 1, 'cid' => -9),
    10 => array( 'lastname' => 'Edwards', 'firstname' => 'Rebecca', 'initials' => 'Z', 'auth_category' => 1, 'cid' => -10),
    11 => array( 'lastname' => "O'Neil", 'firstname' => 'Thomas', 'initials' => 'Z', 'auth_category' => 1, 'cid' => -11),
    12 => array( 'lastname' => 'Smith', 'firstname' => 'Kathrine', 'initials' => 'Z', 'auth_category' => 1, 'cid' => -12),
  );

  // Book Chapter.
  $node = new stdClass();
  $node->nid = -1;
  $node->example_type           = 'Book Chapter';
  $node->title                  = 'A Book Chapter';
  $node->biblio_contributors    = $contributors;
  $node->biblio_type            = 101;
  $node->biblio_year            = 2013;
  $node->biblio_volume          = 1;
  $node->biblio_edition         = 5;
  $node->biblio_issue           = 2;
  $node->biblio_secondary_title = 'My Book Title';
  $node->biblio_pages           = '500-731';
  $node->biblio_coins           = '';

  // Journal Article.
  $node1 = new stdClass();
  $node1->nid = -1;
  $node1->example_type           = 'Journal Article';
  $node1->title                  = 'My Journal Article';
  $node1->biblio_contributors    = $contributors;
  $node1->biblio_type            = 102;
  $node1->biblio_year            = 2011;
  $node1->biblio_volume          = 3;
  $node1->biblio_issue           = 4;
  $node1->biblio_secondary_title = 'The Journal of Articles';
  $node1->biblio_pages           = '25-56';
  $node1->biblio_coins           = '';

  // Book.
  $node2 = new stdClass();
  $node2->nid = -1;
  $node2->example_type           = 'Book with 10+ authors (et al)';
  $node2->title                  = 'This is a Book Title';
  $node2->biblio_contributors    = $contributors_etall;
  $node2->biblio_type            = 100;
  $node2->biblio_year            = 2013;
  $node2->biblio_volume          = 1;
  $node2->biblio_edition         = 5;
  $node2->biblio_pages           = '800';
  $node2->biblio_publisher       = 'Oxford University Press';
  $node2->biblio_place_published = 'Boston, MA';
  $node2->biblio_coins           = '';

  $node_array = array($node, $node1, $node2);

  return $node_array;
}

/**
 * Return a themed citation example.
 *  @params $csl
 *    Citation style to use for theming the citation.
 */
function _os_publications_build_citation_example($csl) {
  if(!isset($csl)) {
    // Get the default biblio style.
    $style = biblio_get_style();
  }else {
    $style = $csl;
  }

  $node_array = _os_publications_get_citation_example();

  return _os_publications_theme_citation(array('style_name' => $style, 'node_array' => $node_array));
}

function _os_publications_theme_citation($variables) {
  global $language;
  $citeproc = '';
  $styled_node = '';
  $node_array = $variables['node_array'];
  $style = isset($variables['style_name']) ? $variables['style_name'] : NULL;

  module_load_include('inc', 'biblio_citeproc', 'CSL');

  if (!$citeproc) {
    $csl_id = ($style) ? $style : biblio_get_style();

    if (strpos($csl_id, '.csl') === FALSE) {// try to convert old style names to csl...
      if (in_array($csl_id, array('ama', 'apa', 'cse', 'ieee', 'mla', 'vancouver'))) {
        $csl_id .= '.csl';
      }
      elseif ($csl_id == 'chicago') {
        $csl_id = 'chicago-fullnote-bibliography.csl';
      }
      else {
        $csl_id = '';
        $message = t('An invalid style "@style" was selected, please check your "CiteProc" style settings.', array('@style' => $csl_id));
        drupal_set_message($message, 'error');
      }
    }
    if (!empty($csl_id)) {
      $csl = db_query('SELECT parent,csl FROM {biblio_citeproc_styles} WHERE filename = :id', array(':id' => $csl_id))->fetchObject();
      if (!isset($csl->csl)) {
        drupal_set_message(t('Biblio-CiteProc could not fetch the style file: !csl_id from the database. Check your CiteProc settings.', array('!csl_id' => $csl_id)), 'error');
        return;
      }
      if (!empty($csl->parent)) {
        $csl_file_contents = db_query("SELECT csl FROM biblio_citeproc_styles WHERE id = :id", array(':id' => $csl->parent))->fetchField();
      }
      else {
        $csl_file_contents = $csl->csl;
      }
      $citeproc = new citeproc($csl_file_contents, $language->language);
    }
  }

  // Display the citation.
  foreach($node_array as $key => $value) {
    $output = '';
    // Strip off the "example_type" array value if one exists.
    if(isset($value->example_type)) {
      $example_type = '<strong>' . $value->example_type . ' ' . t('example:') . '</strong>';
      $output .=  $example_type . '<br />';
    }
    $output .= $citeproc->render($value);
    $styled_node .= '<div class="citation-example">' . $output . '</div>';
  }

  return $styled_node;
}
