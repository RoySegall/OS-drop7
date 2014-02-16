<?php
/**
 * @file
 * vsite_preset.spaces.inc
 */

/**
 * Implements hook_spaces_presets().
 */
function vsite_preset_spaces_presets() {
  $export = array();

  $spaces_presets = new stdClass();
  $spaces_presets->disabled = FALSE; /* Edit this to true to make a default spaces_presets disabled initially */
  $spaces_presets->api_version = 3;
  $spaces_presets->name = 'hwp_administrative';
  $spaces_presets->title = 'HWP Administrative';
  $spaces_presets->description = 'The Harvard Web Publishing standard Adminstrative Department site.';
  $spaces_presets->space_type = 'og';
  $spaces_presets->value = array(
    'bundles' => array(
      0 => 'department',
    ),
    'og_tasks' => array(
      0 => 'vsite_preset_section_about',
      1 => 'vsite_preset_section_news_&_events',
      2 => 'vsite_preset_section_resources',
      3 => 'vsite_preset_section_activities',
      4 => 'vsite_preset_section_services',
      5 => 'vsite_preset_menu_order',
    ),
    'variable' => array(
      'vsite_preset_menu_order' => array(
        'primary-menu' => array(
          'HOME' => -7,
          'Services' => -6,
          'Activities' => -5,
          'People' => -4,
          'Resources' => -3,
          'News & Events' => -2,
          'About' => -1,
        ),
      ),
      'spaces_features' => array(
        'os' => '1',
        'os_pages' => '1',
        'os_news' => '1',
        'os_events' => '1',
        'os_profiles' => '1',
      ),
      'spaces_features_available' => array(
        0 => 'os_blog',
        1 => 'os_booklets',
        2 => 'os_classes',
        3 => 'os_dataverse',
        4 => 'os_events',
        5 => 'os_faq',
        6 => 'os_files_private',
        7 => 'os_image_gallery',
        8 => 'os_links',
        9 => 'os_news',
        10 => 'os_pages',
        11 => 'os_presentations',
        12 => 'os_profiles',
        13 => 'os_publications',
        14 => 'os_reader',
        15 => 'os_software',
        16 => 'harvard_courses',
      ),
      'site_frontpage' => 'home',
      'theme_default' => 'hwpi_classic',
      'os_breadcrumbs_show_breadcrumbs' => 0,
    ),
    'menus' => array(
      'primary-menu' => array(
        900 => array(
          'link_path' => 'home',
          'link_title' => 'HOME',
          'options' => array(),
          'mlid' => 900,
          'p1' => 900,
          'depth' => 1,
          'router_path' => 'home',
          'menu_name' => 'primary-menu',
          'external' => 1,
          'weight' => 0,
          'hidden' => 0,
          'has_children' => 0,
          'expanded' => 0,
          'module' => 'menu',
          'customized' => 0,
          'updated' => 0,
          'plid' => 0,
          'p2' => 0,
          'p3' => 0,
          'p4' => 0,
          'p5' => 0,
          'p6' => 0,
          'p7' => 0,
          'p8' => 0,
          'p9' => 0,
        ),
        902 => array(
          'link_path' => 'people',
          'link_title' => 'People',
          'options' => array(),
          'mlid' => 902,
          'p1' => 902,
          'depth' => 1,
          'router_path' => 'people',
          'menu_name' => 'primary-menu',
          'external' => 1,
          'weight' => 0,
          'hidden' => 0,
          'has_children' => 0,
          'expanded' => 0,
          'module' => 'menu',
          'customized' => 0,
          'updated' => 0,
          'plid' => 0,
          'p2' => 0,
          'p3' => 0,
          'p4' => 0,
          'p5' => 0,
          'p6' => 0,
          'p7' => 0,
          'p8' => 0,
          'p9' => 0,
        ),
      ),
    ),
    'context' => array(
      'os_public:reaction:block' => array(
        'blocks' => array(
          'os-secondary-menu' => array(
            'module' => 'os',
            'delta' => 'secondary-menu',
            'region' => 'header_third',
            'weight' => '-11',
            'status' => 0,
            'title' => '',
          ),
          'os-primary-menu' => array(
            'module' => 'os',
            'delta' => 'primary-menu',
            'region' => 'menu_bar',
            'weight' => '-10',
            'status' => 0,
            'title' => '',
          ),
          'boxes-site_info' => array(
            'module' => 'boxes',
            'delta' => 'site_info',
            'region' => 'header_second',
            'weight' => '-10',
            'status' => 0,
            'title' => '',
          ),
          'os_search_solr-site-search' => array(
            'module' => 'os_search_solr',
            'delta' => 'site-search',
            'region' => 'header_third',
            'weight' => '-10',
            'status' => 0,
            'title' => '',
          ),
        ),
      ),
      'os_front:reaction:block' => array(
        'blocks' => array(),
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('HWP Administrative');
  t('The Harvard Web Publishing standard Adminstrative Department site.');
  $export['hwp_administrative'] = $spaces_presets;

  $spaces_presets = new stdClass();
  $spaces_presets->disabled = FALSE; /* Edit this to true to make a default spaces_presets disabled initially */
  $spaces_presets->api_version = 3;
  $spaces_presets->name = 'hwp_lab_research_group';
  $spaces_presets->title = 'HWP Lab/Research Group';
  $spaces_presets->description = 'The Harvard Web Publishing standard Lab and Research Group site.';
  $spaces_presets->space_type = 'og';
  $spaces_presets->value = array(
    'bundles' => array(
      0 => 'project',
    ),
    'og_tasks' => array(
      0 => 'vsite_preset_section_research',
      1 => 'vsite_preset_section_resources',
      2 => 'vsite_preset_section_news_&_events',
      3 => 'vsite_preset_section_about',
      4 => 'vsite_preset_menu_order',
    ),
    'variable' => array(
      'vsite_preset_menu_order' => array(
        'primary-menu' => array(
          'HOME' => -7,
          'Research' => -6,
          'Publications' => -5,
          'People' => -4,
          'Resources' => -3,
          'News & Events' => -2,
          'About' => -1,
        ),
      ),
      'spaces_features' => array(
        'os' => '1',
        'os_pages' => '1',
        'os_news' => '1',
        'os_events' => '1',
        'os_profiles' => '1',
        'os_publications' => '1',
      ),
      'spaces_features_available' => array(
        0 => 'os_blog',
        1 => 'os_booklets',
        2 => 'os_classes',
        3 => 'os_dataverse',
        4 => 'os_events',
        5 => 'os_faq',
        6 => 'os_files_private',
        7 => 'os_image_gallery',
        8 => 'os_links',
        9 => 'os_news',
        10 => 'os_pages',
        11 => 'os_presentations',
        12 => 'os_profiles',
        13 => 'os_publications',
        14 => 'os_reader',
        15 => 'os_software',
        16 => 'harvard_courses',
      ),
      'site_frontpage' => 'home',
      'theme_default' => 'hwpi_modern',
      'os_breadcrumbs_show_breadcrumbs' => 0,
    ),
    'menus' => array(
      'primary-menu' => array(
        900 => array(
          'link_path' => 'home',
          'link_title' => 'HOME',
          'options' => array(),
          'mlid' => 900,
          'p1' => 900,
          'depth' => 1,
          'router_path' => 'home',
          'menu_name' => 'primary-menu',
          'external' => 1,
          'weight' => 0,
          'hidden' => 0,
          'has_children' => 0,
          'expanded' => 0,
          'module' => 'menu',
          'customized' => 0,
          'updated' => 0,
          'plid' => 0,
          'p2' => 0,
          'p3' => 0,
          'p4' => 0,
          'p5' => 0,
          'p6' => 0,
          'p7' => 0,
          'p8' => 0,
          'p9' => 0,
        ),
        901 => array(
          'link_path' => 'publications',
          'link_title' => 'Publications',
          'options' => array(),
          'mlid' => 901,
          'p1' => 901,
          'depth' => 1,
          'router_path' => 'publications',
          'menu_name' => 'primary-menu',
          'external' => 1,
          'weight' => 0,
          'hidden' => 0,
          'has_children' => 0,
          'expanded' => 0,
          'module' => 'menu',
          'customized' => 0,
          'updated' => 0,
          'plid' => 0,
          'p2' => 0,
          'p3' => 0,
          'p4' => 0,
          'p5' => 0,
          'p6' => 0,
          'p7' => 0,
          'p8' => 0,
          'p9' => 0,
        ),
        902 => array(
          'link_path' => 'people',
          'link_title' => 'People',
          'options' => array(),
          'mlid' => 902,
          'p1' => 902,
          'depth' => 1,
          'router_path' => 'people',
          'menu_name' => 'primary-menu',
          'external' => 1,
          'weight' => 0,
          'hidden' => 0,
          'has_children' => 0,
          'expanded' => 0,
          'module' => 'menu',
          'customized' => 0,
          'updated' => 0,
          'plid' => 0,
          'p2' => 0,
          'p3' => 0,
          'p4' => 0,
          'p5' => 0,
          'p6' => 0,
          'p7' => 0,
          'p8' => 0,
          'p9' => 0,
        ),
      ),
    ),
    'context' => array(
      'os_public:reaction:block' => array(
        'blocks' => array(
          'os-secondary-menu' => array(
            'module' => 'os',
            'delta' => 'secondary-menu',
            'region' => 'header_third',
            'weight' => '-11',
            'status' => 0,
            'title' => '',
          ),
          'os-primary-menu' => array(
            'module' => 'os',
            'delta' => 'primary-menu',
            'region' => 'menu_bar',
            'weight' => '-10',
            'status' => 0,
            'title' => '',
          ),
          'boxes-site_info' => array(
            'module' => 'boxes',
            'delta' => 'site_info',
            'region' => 'header_second',
            'weight' => '-10',
            'status' => 0,
            'title' => '',
          ),
          'os_search_solr-site-search' => array(
            'module' => 'os_search_solr',
            'delta' => 'site-search',
            'region' => 'header_third',
            'weight' => '-10',
            'status' => 0,
            'title' => '',
          ),
        ),
      ),
      'os_front:reaction:block' => array(
        'blocks' => array(),
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('HWP Lab/Research Group');
  t('The Harvard Web Publishing standard Lab and Research Group site.');
  $export['hwp_lab_research_group'] = $spaces_presets;

  $spaces_presets = new stdClass();
  $spaces_presets->disabled = FALSE; /* Edit this to true to make a default spaces_presets disabled initially */
  $spaces_presets->api_version = 3;
  $spaces_presets->name = 'hwp_project';
  $spaces_presets->title = 'HWP Project';
  $spaces_presets->description = 'The Harvard Web Publishing standard Project site.';
  $spaces_presets->space_type = 'og';
  $spaces_presets->value = array(
    'bundles' => array(
      0 => 'project',
    ),
    'og_tasks' => array(
      0 => 'vsite_preset_section_overview',
      1 => 'vsite_preset_section_activities',
      2 => 'vsite_preset_section_resources',
      3 => 'vsite_preset_section_news_&_events',
      4 => 'vsite_preset_section_about',
      5 => 'vsite_preset_menu_order',
    ),
    'variable' => array(
      'vsite_preset_menu_order' => array(
        'primary-menu' => array(
          'HOME' => -7,
          'Overview' => -6,
          'Activities' => -5,
          'People' => -4,
          'Resources' => -3,
          'News & Events' => -2,
          'About' => -1,
        ),
      ),
      'spaces_features' => array(
        'os' => '1',
        'os_pages' => '1',
        'os_news' => '1',
        'os_events' => '1',
        'os_profiles' => '1',
      ),
      'spaces_features_available' => array(
        0 => 'os_blog',
        1 => 'os_booklets',
        2 => 'os_classes',
        3 => 'os_dataverse',
        4 => 'os_events',
        5 => 'os_faq',
        6 => 'os_files_private',
        7 => 'os_image_gallery',
        8 => 'os_links',
        9 => 'os_news',
        10 => 'os_pages',
        11 => 'os_presentations',
        12 => 'os_profiles',
        13 => 'os_publications',
        14 => 'os_reader',
        15 => 'os_software',
        16 => 'harvard_courses',
      ),
      'site_frontpage' => 'home',
      'theme_default' => 'hwpi_modern',
      'os_breadcrumbs_show_breadcrumbs' => 0,
    ),
    'menus' => array(
      'primary-menu' => array(
        900 => array(
          'link_path' => 'home',
          'link_title' => 'HOME',
          'options' => array(),
          'mlid' => 900,
          'p1' => 900,
          'depth' => 1,
          'router_path' => 'home',
          'menu_name' => 'primary-menu',
          'external' => 1,
          'weight' => 0,
          'hidden' => 0,
          'has_children' => 0,
          'expanded' => 0,
          'module' => 'menu',
          'customized' => 0,
          'updated' => 0,
          'plid' => 0,
          'p2' => 0,
          'p3' => 0,
          'p4' => 0,
          'p5' => 0,
          'p6' => 0,
          'p7' => 0,
          'p8' => 0,
          'p9' => 0,
        ),
        902 => array(
          'link_path' => 'people',
          'link_title' => 'People',
          'options' => array(),
          'mlid' => 902,
          'p1' => 902,
          'depth' => 1,
          'router_path' => 'people',
          'menu_name' => 'primary-menu',
          'external' => 1,
          'weight' => 0,
          'hidden' => 0,
          'has_children' => 0,
          'expanded' => 0,
          'module' => 'menu',
          'customized' => 0,
          'updated' => 0,
          'plid' => 0,
          'p2' => 0,
          'p3' => 0,
          'p4' => 0,
          'p5' => 0,
          'p6' => 0,
          'p7' => 0,
          'p8' => 0,
          'p9' => 0,
        ),
      ),
    ),
    'context' => array(
      'os_public:reaction:block' => array(
        'blocks' => array(
          'os-secondary-menu' => array(
            'module' => 'os',
            'delta' => 'secondary-menu',
            'region' => 'header_third',
            'weight' => '-11',
            'status' => 0,
            'title' => '',
          ),
          'os-primary-menu' => array(
            'module' => 'os',
            'delta' => 'primary-menu',
            'region' => 'menu_bar',
            'weight' => '-10',
            'status' => 0,
            'title' => '',
          ),
          'boxes-site_info' => array(
            'module' => 'boxes',
            'delta' => 'site_info',
            'region' => 'header_second',
            'weight' => '-10',
            'status' => 0,
            'title' => '',
          ),
          'os_search_solr-site-search' => array(
            'module' => 'os_search_solr',
            'delta' => 'site-search',
            'region' => 'header_third',
            'weight' => '-10',
            'status' => 0,
            'title' => '',
          ),
        ),
      ),
      'os_front:reaction:block' => array(
        'blocks' => array(),
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('HWP Project');
  t('The Harvard Web Publishing standard Project site.');
  $export['hwp_project'] = $spaces_presets;

  $spaces_presets = new stdClass();
  $spaces_presets->disabled = FALSE; /* Edit this to true to make a default spaces_presets disabled initially */
  $spaces_presets->api_version = 3;
  $spaces_presets->name = 'hwp_personal';
  $spaces_presets->title = 'HWP Personal';
  $spaces_presets->description = 'The Harvard Web Publishing standard Personal site.';
  $spaces_presets->space_type = 'og';
  $spaces_presets->value = array(
    'bundles' => array('personal'),
    'variable' => array(
      'spaces_features' => array(
        'os' => '1',
        'os_pages' => '1',
        'os_biocv' => '1',
        'os_publications' => '1',
        'os_classes' => '1',
      ),
      'spaces_features_available' => array(
        'os_blog',
        'os_booklets',
        'os_classes',
        'os_dataverse',
        'os_events',
        'os_faq',
        'os_files_private',
        'os_image_gallery',
        'os_links',
        'os_news',
        'os_pages',
        'os_presentations',
        'os_profiles',
        'os_publications',
        'os_reader',
        'os_software',
        'harvard_courses',
      ),
      'site_frontpage' => 'home',
      'theme_default' => 'hwpi_classic',
      'os_appearance_hwpi_classic_flavor' => 'classic_indigo',
      'os_breadcrumbs_show_breadcrumbs' => 0,
    ),
    'menus' => array(
      'primary-menu' => array(
        900 => array(
          'link_path' => 'biocv',
          'link_title' => 'Bio & CV',
          'options' => array(),
          'mlid' => 900,
          'p1' => 900,
          'depth' => 1,
          'router_path' => 'biocv',
          'menu_name' => 'primary-menu',
          'external' => 1,
          'weight' => -3,
          'hidden' => 0,
          'has_children' => 0,
          'expanded' => 0,
          'module' => 'menu',
          'customized' => 0,
          'updated' => 0,
          'plid' => 0,
          'p2' => 0,
          'p3' => 0,
          'p4' => 0,
          'p5' => 0,
          'p6' => 0,
          'p7' => 0,
          'p8' => 0,
          'p9' => 0,
        ),
        901 => array(
          'link_path' => 'publications',
          'link_title' => 'Publications',
          'options' => array(),
          'mlid' => 901,
          'p1' => 901,
          'depth' => 1,
          'router_path' => 'publications',
          'menu_name' => 'primary-menu',
          'external' => 1,
          'weight' => -2,
          'hidden' => 0,
          'has_children' => 0,
          'expanded' => 0,
          'module' => 'menu',
          'customized' => 0,
          'updated' => 0,
          'plid' => 0,
          'p2' => 0,
          'p3' => 0,
          'p4' => 0,
          'p5' => 0,
          'p6' => 0,
          'p7' => 0,
          'p8' => 0,
          'p9' => 0,
        ),
        902 => array(
          'link_path' => 'classes',
          'link_title' => 'Classes',
          'options' => array(),
          'mlid' => 902,
          'p1' => 902,
          'depth' => 1,
          'router_path' => 'classes',
          'menu_name' => 'primary-menu',
          'external' => 1,
          'weight' => -1,
          'hidden' => 0,
          'has_children' => 0,
          'expanded' => 0,
          'module' => 'menu',
          'customized' => 0,
          'updated' => 0,
          'plid' => 0,
          'p2' => 0,
          'p3' => 0,
          'p4' => 0,
          'p5' => 0,
          'p6' => 0,
          'p7' => 0,
          'p8' => 0,
          'p9' => 0,
        ),
      ),
    ),
    'context' => array(
      'os_public:reaction:block' => array(
        'blocks' => array(
          'os-secondary-menu' => array(
            'module' => 'os',
            'delta' => 'secondary-menu',
            'region' => 'header_third',
            'weight' => '-11',
            'status' => 0,
            'title' => '',
          ),
          'os-primary-menu' => array(
            'module' => 'os',
            'delta' => 'primary-menu',
            'region' => 'menu_bar',
            'weight' => '-10',
            'status' => 0,
            'title' => '',
          ),
          'boxes-site_logo' => array(
            'module' => 'boxes',
            'delta' => 'site_logo',
            'region' => 'header_first',
            'weight' => '-10',
            'status' => 0,
            'title' => '',
          ),
          'boxes-site_info' => array(
            'module' => 'boxes',
            'delta' => 'site_info',
            'region' => 'header_second',
            'weight' => '-10',
            'status' => 0,
            'title' => '',
          ),
          'os_search_solr-site-search' => array(
            'module' => 'os_search_solr',
            'delta' => 'site-search',
            'region' => 'header_third',
            'weight' => '-10',
            'status' => 0,
            'title' => '',
          ),
          'boxes-hwp_personal_contact_html' => array(
            'module' => 'boxes',
            'delta' => 'hwp_personal_contact_html',
            'region' => 'sidebar_second',
            'weight' => '-10',
          ),
        ),
      ),
      'os_front:reaction:block' => array(
        'blocks' => array(),
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('HWP Personal');
  t('The Harvard Web Publishing standard Personal site.');
  $export['hwp_personal'] = $spaces_presets;

  return $export;
}
