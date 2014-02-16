<?php

///////////////////////
// Terms

/**
 * Migrate "Authors" terms.
 */
class OsMigrateAuthorsTaxonomyTerm extends OsMigrate {

  public $dependencies = array(
    'OsMigratePersonalNode',
  );

  public $entityType = 'taxonomy_term';
  public $bundle = 'authors';

  public $ogVocab = TRUE;
}

/**
 * Migrate "Biology" terms.
 */
class OsMigrateBiologyTaxonomyTerm extends OsMigrate {

  public $dependencies = array(
    'OsMigratePersonalNode',
  );

  public $entityType = 'taxonomy_term';
  public $bundle = 'biology';

  public $ogVocab = TRUE;
}

/**
 * Migrate "Math" terms.
 */
class OsMigrateMathTaxonomyTerm extends OsMigrate {

  public $dependencies = array(
    'OsMigratePersonalNode',
  );

  public $entityType = 'taxonomy_term';
  public $bundle = 'math';

  public $ogVocab = TRUE;
}

/**
 * Migrate "Science" terms.
 */
class OsMigrateScienceTaxonomyTerm extends OsMigrate {

  public $dependencies = array(
    'OsMigratePersonalNode',
  );

  public $entityType = 'taxonomy_term';
  public $bundle = 'science';

  public $ogVocab = TRUE;
}

/**
 * Migrate "Authors" terms.
 */
class OsMigrateFamilyTaxonomyTerm extends OsMigrate {

  public $dependencies = array(
    'OsMigratePersonalNode',
  );

  public $entityType = 'taxonomy_term';
  public $bundle = 'family';

  public $ogVocab = TRUE;
}

///////////////////////
// Nodes

/**
 * Migrate "Personal" node.
 */
class OsMigratePersonalNode extends OsMigrate {
  public $entityType = 'node';
  public $bundle = 'personal';

  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('title', 'Title'),
    array('purl', 'URL'),
    array('public', 'Public'),
    array('domain', 'Domain'),
    array(VSITE_ACCESS_FIELD, 'Access'),
    array('uid', 'UID'),
    array('members', 'Members'),
    array('field_group_parent', 'Parent group'),
  );

  public $dependencies = array(
    'OsMigrateUsers',
    'OsMigrateDepartmentNode',
  );

  public function __construct() {
    parent::__construct();
    $this->addFieldMapping('purl', 'purl');
    $this->addFieldMapping('field_site_address', 'purl');
    $this->addFieldMapping(VSITE_ACCESS_FIELD, VSITE_ACCESS_FIELD);

    $this->addFieldMapping('uid', 'uid')
      ->sourceMigration('OsMigrateUsers');

    $this->addFieldMapping('users_to_group', 'members')
      ->sourceMigration('OsMigrateUsers')
      ->separator('|');

    $this->addFieldMapping('field_group_parent', 'field_group_parent')
      ->sourceMigration('OsMigrateDepartmentNode');
  }

  /**
   * Creating the PURL address for the personal site.
   */
  public function prepare($entity, $row) {
    $entity->purl = array('value' => $row->purl);

    $value = $entity->field_site_address[LANGUAGE_NONE][0]['value'];
    $entity->field_site_address[LANGUAGE_NONE][0]['value'] = variable_get('purl_base_domain') . '/' . $value;

    // This is a private site.
    if ($row->public == 'private') {
      $entity->{OG_ACCESS_FIELD}[LANGUAGE_NONE][0]['value'] = TRUE;
    }
  }

  /**
   * Group the users with the create group.
   */
  function complete($entity, $row) {
    if (is_array($entity->users_to_group)) {
      foreach ($entity->users_to_group as $uid) {
        og_group('node', $entity->nid, array(
          'entity' => $uid,
        ));
      }
    }
    else {
      og_group('node', $entity->nid, array(
        'entity' => $entity->users_to_group,
      ));
    }
  }
}

/**
 * Migrate "Department" node.
 */
class OsMigrateDepartmentNode extends OsMigrate {
  public $entityType = 'node';
  public $bundle = 'department';

  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('title', 'Title'),
    array('purl', 'URL'),
    array('public', 'Public'),
    array('domain', 'Domain'),
    array(VSITE_ACCESS_FIELD, 'Access'),
    array('uid', 'UID'),
    array('members', 'Members'),
  );

  public $dependencies = array(
    'OsMigrateUsers',
  );

  public function __construct() {
    parent::__construct();
    $this->addFieldMapping('purl', 'purl');
    $this->addFieldMapping('field_site_address', 'purl');
    $this->addFieldMapping(VSITE_ACCESS_FIELD, VSITE_ACCESS_FIELD);

    $this->addFieldMapping('uid', 'uid')
      ->sourceMigration('OsMigrateUsers');

    $this->addFieldMapping('users_to_group', 'members')
      ->sourceMigration('OsMigrateUsers')
      ->separator('|');
  }

  /**
   * Creating the PURL address for the personal site.
   */
  public function prepare($entity, $row) {
    $entity->purl = array('value' => $row->purl);

    $value = $entity->field_site_address[LANGUAGE_NONE][0]['value'];
    $entity->field_site_address[LANGUAGE_NONE][0]['value'] = variable_get('purl_base_domain') . '/' . $value;

    // This is a private site.
    if ($row->public == 'private') {
      $entity->{OG_ACCESS_FIELD}[LANGUAGE_NONE][0]['value'] = TRUE;
    }
  }

  /**
   * Group the users with the create group.
   */
  function complete($entity, $row) {
    if ($row->domain) {
      $nid = entity_id($this->entityType, $entity);
      os_migrate_demo_spaces_overrides('og', $nid, $row->domain);
    }

    if (is_array($entity->users_to_group)) {
      foreach ($entity->users_to_group as $uid) {
        og_group('node', $entity->nid, array(
          'entity' => $uid,
        ));
      }
    }
    else {
      og_group('node', $entity->nid, array(
        'entity' => $entity->users_to_group,
      ));
    }
  }
}

/**
 * Migrate "Project" node.
 */
class OsMigrateProjectNode extends OsMigrate {
  public $entityType = 'node';
  public $bundle = 'project';

  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('title', 'Title'),
    array('purl', 'URL'),
    array('uid', 'UID'),
  );

  public $dependencies = array(
    'OsMigrateUsers',
  );

  public function __construct() {
    parent::__construct();
    $this->addFieldMapping('purl', 'purl');
    $this->addFieldMapping('field_site_address', 'purl');

    $this->addFieldMapping('uid', 'uid')
      ->sourceMigration('OsMigrateUsers');
  }

  /**
   * Creating the PURL address for the personal site.
   */
  public function prepare($entity, $row) {
    $entity->purl = array('value' => $row->purl);

    $value = $entity->field_site_address[LANGUAGE_NONE][0]['value'];
    $entity->field_site_address[LANGUAGE_NONE][0]['value'] = variable_get('purl_base_domain') . '/' . $value;
  }
}

/**
 * Migrate "Biography" node.
 */
class OsMigrateBioagrphyNode extends OsMigrate {
  public $entityType = 'node';
  public $bundle = 'bio';

  public $csvColumns = array(
    array('id', 'ID'),
    array('title', 'Title'),
    array('body', 'Body'),
    array(OG_AUDIENCE_FIELD, 'Site'),
    array('uid', 'UID'),
  );

  public $dependencies = array(
    'OsMigratePersonalNode',
    'OsMigrateProjectNode',
    'OsMigrateUsers',
  );

  public function __construct() {
    parent::__construct();

    $this->addFieldMapping('body', 'body');
    $this->addFieldMapping(OG_AUDIENCE_FIELD, OG_AUDIENCE_FIELD)
      ->sourceMigration(array('OsMigratePersonalNode', 'OsMigrateProjectNode'));

    $this->addFieldMapping('uid', 'uid')
      ->sourceMigration('OsMigrateUsers');
  }
}

/**
 * Migrate "Software" node.
 */
class OsMigrateSoftwareNode extends OsMigrate {
  public $entityType = 'node';
  public $bundle = 'software_project';

  public $csvColumns = array(
    array('id', 'ID'),
    array('title', 'Title'),
    array('body', 'Body'),
    array(OG_AUDIENCE_FIELD, 'Site'),
    array(OG_VOCAB_FIELD, 'Terms'),
    array('uid', 'UID'),
  );

  public $dependencies = array(
    'OsMigratePersonalNode',
    'OsMigrateProjectNode',
    'OsMigrateUsers',
  );

  public function __construct() {
    parent::__construct();

    $this->addFieldMapping('body', 'body');
    $this->addFieldMapping(OG_AUDIENCE_FIELD, OG_AUDIENCE_FIELD)
      ->sourceMigration(array('OsMigratePersonalNode', 'OsMigrateProjectNode'));
    $this->addFieldMapping(OG_VOCAB_FIELD, OG_VOCAB_FIELD)
      ->sourceMigration(array('OsMigrateScienceTaxonomyTerm'))
      ->separator('|');

    $this->addFieldMapping('uid', 'uid')
      ->sourceMigration('OsMigrateUsers');
  }
}

/**
 * Migrating books.
 */
class OsMigratePublicationNode extends OsMigrate {
  public $entityType = 'node';
  public $bundle = 'biblio';

  public $csvColumns = array(
    array('id', 'ID'),
    array('title', 'Title'),
    array('biblio_place_published', 'Publisher'),
    array('biblio_year', 'Year'),
    array('biblio_place_published', 'Publish location'),
    array('biblio_type_name', 'Biblio type name'),
    array('biblio_type', 'Biblio type'),
    array(OG_AUDIENCE_FIELD, 'Site'),
    array(OG_VOCAB_FIELD, 'Terms'),
    array('uid', 'UID'),
    array('created', 'Created'),
  );

  public $dependencies = array(
    'OsMigratePersonalNode',
    'OsMigrateProjectNode',
    'OsMigrateScienceTaxonomyTerm',
    'OsMigrateUsers',
  );

  public function __construct() {
    parent::__construct();

    $this->addFieldMapping('biblio_place_published', 'biblio_place_published');
    $this->addFieldMapping('biblio_year', 'biblio_year');
    $this->addFieldMapping('Publish location', 'biblio_place_published');
    $this->addFieldMapping('biblio_type_name', 'biblio_type_name');
    $this->addFieldMapping('biblio_type', 'biblio_type');
    $this->addFieldMapping(OG_AUDIENCE_FIELD, OG_AUDIENCE_FIELD)
      ->sourceMigration(array('OsMigratePersonalNode', 'OsMigrateProjectNode'));
    $this->addFieldMapping(OG_VOCAB_FIELD, OG_VOCAB_FIELD)
      ->sourceMigration(array('OsMigrateScienceTaxonomyTerm'))
      ->separator('|');
    $this->addFieldMapping('uid', 'uid')
      ->sourceMigration('OsMigrateUsers');
    $this->addFieldMapping('created', 'created');
  }


  public function prepareRow($row) {
    // The 'Created' column is optional and defaults to now.
    $row->created = !empty($row->created) ? $row->created : time();
  }

  /**
   * When creating a new publication, the biblio module mange the fields
   * differently and consider them as properties and not fields. The prepare
   * function will deal with that.
   */
  public function prepare($entity, $row) {
    foreach ($row as $row_key => $row_value) {
      if (in_array($row_key, array('id', 'title', 'og_group_ref', 'uid', OG_VOCAB_FIELD))) {
        continue;
      }

      $entity->$row_key = $row_value;
    }
  }
}

/**
 * Migrating classes.
 */
class OsMigrateClassesNode extends OsMigrate {
  public $entityType = 'node';
  public $bundle = 'class';

  public $csvColumns = array(
    array('id', 'ID'),
    array('title', 'Title'),
    array('body', 'Body'),
    array('link', 'Link'),
    array('semester', 'Semester'),
    array(OG_AUDIENCE_FIELD, 'Site'),
    array(OG_VOCAB_FIELD, 'Terms'),
    array('path', 'Path'),
    array('uid', 'UID'),
  );

  public $dependencies = array(
    'OsMigratePersonalNode',
    'OsMigrateProjectNode',
    'OsMigrateScienceTaxonomyTerm',
    'OsMigrateUsers',
  );

  public function __construct() {
    parent::__construct();

    $this->addFieldMapping('body', 'body');
    $this->addFieldMapping('field_semester', 'semester');

    $this->addFieldMapping(OG_AUDIENCE_FIELD, OG_AUDIENCE_FIELD)
      ->sourceMigration(array('OsMigrateProjectNode', 'OsMigratePersonalNode'));

    $this->addFieldMapping(OG_VOCAB_FIELD, OG_VOCAB_FIELD)
      ->sourceMigration(array('OsMigrateScienceTaxonomyTerm'))
      ->separator('|');

    $this->addFieldMapping('path', 'path');

    $this->addFieldMapping('uid', 'uid')
      ->sourceMigration('OsMigrateUsers');
  }

  /**
   * Dealing with the link url field.
   */
  public function prepare($entity, $row) {
    $link = explode(";", $row->link);

    $entity->field_class_link[LANGUAGE_NONE][0]['url'] = $link[0];
    $entity->field_class_link[LANGUAGE_NONE][0]['title'] = $link[1];

    if (!empty($row->path)) {
      // Disable path-auto.
      $entity->path['pathauto'] = FALSE;
    }
  }
}

/**
 * Migrate classes material.
 */
class OsMigrateClassesMaterialNode extends OsMigrate {
  public $entityType = 'node';
  public $bundle = 'class_material';

  public $csvColumns = array(
    array('id', 'ID'),
    array('title', 'Title'),
    array('body', 'Body'),
    array('field_class', 'Class'),
    array(OG_AUDIENCE_FIELD, 'Site'),
    array('uid', 'UID'),
  );

  public $dependencies = array(
    'OsMigratePersonalNode',
    'OsMigrateProjectNode',
    'OsMigrateClassesNode',
    'OsMigrateUsers',
  );

  public function __construct() {
    parent::__construct();

    $this->addFieldMapping('body', 'body');
    $this->addFieldMapping(OG_AUDIENCE_FIELD, OG_AUDIENCE_FIELD)
      ->sourceMigration(array('OsMigratePersonalNode', 'OsMigrateProjectNode'));
    $this->addFieldMapping('field_class', 'field_class')
      ->sourceMigration('OsMigrateClassesNode');

    $this->addFieldMapping('uid', 'uid')
      ->sourceMigration('OsMigrateUsers');
  }
}

/**
 * Migrate curriculum vitae.
 */
class OsMigrateCurriculumVitaeNode extends OsMigrate {
  public $entityType = 'node';
  public $bundle = 'cv';

  public $csvColumns = array(
    array('id', 'ID'),
    array('title', 'Title'),
    array('body', 'Body'),
    array(OG_AUDIENCE_FIELD, 'Site'),
    array('uid', 'UID'),
  );

  public $dependencies = array(
    'OsMigratePersonalNode',
    'OsMigrateProjectNode',
    'OsMigrateUsers',
  );

  public function __construct() {
    parent::__construct();

    $this->addFieldMapping('body', 'body');
    $this->addFieldMapping(OG_AUDIENCE_FIELD, OG_AUDIENCE_FIELD)
      ->sourceMigration(array('OsMigratePersonalNode', 'OsMigrateProjectNode'));

    $this->addFieldMapping('uid', 'uid')
      ->sourceMigration('OsMigrateUsers');
  }
}

/**
 * Migrate news.
 */
class OsMigrateNewsNode extends OsMigrate {
  public $entityType = 'node';
  public $bundle = 'news';

  public $csvColumns = array(
    array('id', 'ID'),
    array('title', 'Title'),
    array('body', 'Body'),
    array(OG_AUDIENCE_FIELD, 'Site'),
    array(OG_VOCAB_FIELD, 'Terms'),
    array('uid', 'UID'),
  );

  public $dependencies = array(
    'OsMigratePersonalNode',
    'OsMigrateProjectNode',
    'OsMigrateUsers',
  );

  public function __construct() {
    parent::__construct();

    $this->addFieldMapping('body', 'body');
    $this->addFieldMapping(OG_AUDIENCE_FIELD, OG_AUDIENCE_FIELD)
      ->sourceMigration(array('OsMigratePersonalNode', 'OsMigrateProjectNode'));

    $this->addFieldMapping(OG_VOCAB_FIELD, OG_VOCAB_FIELD)
      ->sourceMigration(array('OsMigrateScienceTaxonomyTerm'))
      ->separator('|');

    $this->addFieldMapping('uid', 'uid')
      ->sourceMigration('OsMigrateUsers');
  }
}

/**
 * Migrate events.
 */
class OsMigrateEventsNode extends OsMigrate {
  public $entityType = 'node';
  public $bundle = 'event';

  public $csvColumns = array(
    array('id', 'ID'),
    array('title', 'Title'),
    array('body', 'Body'),
    array('field_date', 'Timestamp'),
    array(OG_AUDIENCE_FIELD, 'Site'),
    array(OG_VOCAB_FIELD, 'Terms'),
    array('uid', 'UID'),
  );

  public $dependencies = array(
    'OsMigratePersonalNode',
    'OsMigrateProjectNode',
    'OsMigrateAuthorsTaxonomyTerm',
    'OsMigrateUsers',
  );

  public function __construct() {
    parent::__construct();

    $this->addFieldMapping('body', 'body');
    $this->addFieldMapping('field_date', 'field_date');
    $this->addFieldMapping(OG_AUDIENCE_FIELD, OG_AUDIENCE_FIELD)
      ->sourceMigration(array('OsMigratePersonalNode', 'OsMigrateProjectNode'));
    $this->addFieldMapping(OG_VOCAB_FIELD, OG_VOCAB_FIELD)
      ->sourceMigration(array('OsMigrateAuthorsTaxonomyTerm'))
      ->separator('|');

    $this->addFieldMapping('uid', 'uid')
      ->sourceMigration('OsMigrateUsers');
  }

  public function prepare($entity, $row) {
    $date = explode(';', $row->field_date);

    if ($date[0] == 'now') {
      $date[0] = date('Y-m-d H:i', time());
    }

    $entity->field_date[LANGUAGE_NONE][0] = array(
       'value' => $date[0],
       'date_type' => 'datetime',
    );

    // Adding the end date of the event.
    if (isset($date[1])) {
      if ($date[1] == 'now') {
        $date[1] = date('Y-m-d H:i', time());
      }

      $entity->field_date[LANGUAGE_NONE][0]['value2'] = $date[1];
    }
  }
}

/**
 * Migrate FAQs.
 */
class OsMigrateFAQNode extends OsMigrate {
  public $entityType = 'node';
  public $bundle = 'faq';

  public $csvColumns = array(
    array('id', 'ID'),
    array('title', 'Title'),
    array('body', 'Body'),
    array(OG_AUDIENCE_FIELD, 'Site'),
    array(OG_VOCAB_FIELD, 'Terms'),
    array('uid', 'UID'),
  );

  public $dependencies = array(
    'OsMigratePersonalNode',
    'OsMigrateScienceTaxonomyTerm',
    'OsMigrateUsers',
  );

  public function __construct() {
    parent::__construct();

    $this->addFieldMapping('body', 'body');
    $this->addFieldMapping(OG_AUDIENCE_FIELD, OG_AUDIENCE_FIELD)
      ->sourceMigration('OsMigratePersonalNode');
    $this->addFieldMapping(OG_VOCAB_FIELD, OG_VOCAB_FIELD)
      ->sourceMigration(array('OsMigrateScienceTaxonomyTerm'))
      ->separator('|');

    $this->addFieldMapping('uid', 'uid')
      ->sourceMigration('OsMigrateUsers');
  }
}

/**
 * Migrate Blog.
 */
class OsMigrateBlogNode extends OsMigrate {
  public $entityType = 'node';
  public $bundle = 'blog';

  public $csvColumns = array(
    array('id', 'ID'),
    array('title', 'Title'),
    array('body', 'Body'),
    array(OG_AUDIENCE_FIELD, 'Site'),
    array(OG_VOCAB_FIELD, 'Terms'),
    array('uid', 'UID'),
    array('status','Status'),
  );

  public $dependencies = array(
    'OsMigratePersonalNode',
    'OsMigrateProjectNode',
    'OsMigrateUsers',
  );

  public function __construct() {
    parent::__construct();

    $this->addFieldMapping('body', 'body');
    $this->addFieldMapping(OG_AUDIENCE_FIELD, OG_AUDIENCE_FIELD)
      ->sourceMigration(array('OsMigrateProjectNode', 'OsMigratePersonalNode'));
    $this->addFieldMapping(OG_VOCAB_FIELD, OG_VOCAB_FIELD)
      ->sourceMigration(array('OsMigrateScienceTaxonomyTerm'))
      ->separator('|');

    $this->addFieldMapping('uid', 'uid')
      ->sourceMigration('OsMigrateUsers');

    $this->addFieldMapping('status', 'status')
      ->defaultValue(NODE_PUBLISHED);
  }

  public function prepare($entity, $row) {
    // Make sure node has comments.
    $entity->comment = COMMENT_NODE_OPEN;
  }
}

/**
 * Migrate documents.
 */
class OsMigrateBookNode extends OsMigrate {
  public $entityType = 'node';
  public $bundle = 'book';

  public $csvColumns = array(
    array('id', 'ID'),
    array('title', 'Title'),
    array('body', 'Body'),
    array(OG_AUDIENCE_FIELD, 'Site'),
    array(OG_VOCAB_FIELD, 'Terms'),
    array('uid', 'UID'),
  );

  public $dependencies = array(
    'OsMigratePersonalNode',
    'OsMigrateProjectNode',
    'OsMigrateUsers',
  );

  public function __construct() {
    parent::__construct();

    $this->addFieldMapping('body', 'body');
    $this->addFieldMapping(OG_AUDIENCE_FIELD, OG_AUDIENCE_FIELD)
      ->sourceMigration(array('OsMigratePersonalNode', 'OsMigrateProjectNode'));

    $this->addFieldMapping(OG_VOCAB_FIELD, OG_VOCAB_FIELD)
      ->sourceMigration(array('OsMigrateScienceTaxonomyTerm'))
      ->separator('|');

    $this->addFieldMapping('uid', 'uid')
      ->sourceMigration('OsMigrateUsers');
  }

  public function prepare($entity, $row) {
    // Let know the book module that this is a new book.
    $entity->book = array(
      'bid' => 'new',
    );
  }
}

/**
 * Migrate people.
 */
class OsMigratePeopleNode extends OsMigrate {
  public $entityType = 'node';
  public $bundle = 'person';

  public $csvColumns = array(
    array('id', 'ID'),
    array('title', 'First name'),
    array('middle_name', 'Middle name'),
    array('last_name', 'Last name'),
    array('phone', 'Phone'),
    array('professional_titles', 'Professional titles'),
    array('address', 'Address'),
    array('email', 'E-mail'),
    array('websites', 'Websites'),
    array('body', 'Body'),
    array(OG_AUDIENCE_FIELD, 'Site'),
    array(OG_VOCAB_FIELD, 'Terms'),
    array('uid', 'UID'),
  );

  public $dependencies = array(
    'OsMigratePersonalNode',
    'OsMigrateProjectNode',
    'OsMigrateScienceTaxonomyTerm',
    'OsMigrateUsers',
  );

  public function __construct() {
    parent::__construct();

    $this->addFieldMapping('field_middle_name_or_initial', 'middle_name');
    $this->addFieldMapping('field_last_name', 'last_name');
    $this->addFieldMapping('field_phone', 'phone');
    $this->addFieldMapping('field_email', 'email');
    $this->addFieldMapping('field_address', 'address');
    $this->addFieldMapping('body', 'body');
    $this->addFieldMapping('field_professional_title', 'professional_titles')->separator(';');
    $this->addFieldMapping(OG_AUDIENCE_FIELD, OG_AUDIENCE_FIELD)
      ->sourceMigration(array('OsMigratePersonalNode', 'OsMigrateProjectNode'));
    $this->addFieldMapping(OG_VOCAB_FIELD, OG_VOCAB_FIELD)
      ->sourceMigration(array('OsMigrateScienceTaxonomyTerm'))
      ->separator('|');

    $this->addFieldMapping('uid', 'uid')
      ->sourceMigration('OsMigrateUsers');
  }

  public function prepare($entity, $row) {
    // Inserting the first name - title - into the first name field.
    $entity->field_first_name[LANGUAGE_NONE][0]['value'] = $entity->title;

    // Handeling websites.
    if (!empty($row->websites)) {
      $websites = explode(';', $row->websites);
      foreach ($websites as $key => $website) {
        $link = explode('|', $website);

        $entity->field_website[LANGUAGE_NONE][$key] = array(
          'title' => $link[0],
          'url' => $link[1],
        );
      }
    }
  }
}

/**
 * Migrate Link.
 */
class OsMigrateLinkNode extends OsMigrate {
  public $entityType = 'node';
  public $bundle = 'link';

  public $csvColumns = array(
    array('id', 'ID'),
    array('title', 'Title'),
    array('body', 'Body'),
    array('link', 'Link'),
    array(OG_AUDIENCE_FIELD, 'Site'),
    array(OG_VOCAB_FIELD, 'Terms'),
    array('uid', 'UID'),
  );

  public $dependencies = array(
    'OsMigratePersonalNode',
    'OsMigrateProjectNode',
    'OsMigrateScienceTaxonomyTerm',
    'OsMigrateUsers',
  );

  public function __construct() {
    parent::__construct();

    $this->addFieldMapping('body', 'body');
    $this->addFieldMapping(OG_AUDIENCE_FIELD, OG_AUDIENCE_FIELD)
      ->sourceMigration(array('OsMigratePersonalNode', 'OsMigrateProjectNode'));
    $this->addFieldMapping(OG_VOCAB_FIELD, OG_VOCAB_FIELD)
      ->sourceMigration(array('OsMigrateScienceTaxonomyTerm'))
      ->separator('|');

    $this->addFieldMapping('uid', 'uid')
      ->sourceMigration('OsMigrateUsers');
  }

  public function prepare($entity, $row) {
    $entity->field_links_link[LANGUAGE_NONE][0]['url'] = $row->link;
  }
}

/**
 * Migrate presentation.
 */
class OsMigratePresntationsNode extends OsMigrate {
  public $entityType = 'node';
  public $bundle = 'presentation';

  public $csvColumns = array(
    array('id', 'ID'),
    array('title', 'Title'),
    array('body', 'Body'),
    array('date', 'Date'),
    array('location', 'Locations'),
    array(OG_AUDIENCE_FIELD, 'Site'),
    array(OG_VOCAB_FIELD, 'Terms'),
    array('uid', 'UID'),
  );

  public $dependencies = array(
    'OsMigratePersonalNode',
    'OsMigrateProjectNode',
    'OsMigrateScienceTaxonomyTerm',
    'OsMigrateUsers',
  );

  public function __construct() {
    parent::__construct();

    $this->addFieldMapping('body', 'body');
    $this->addFieldMapping('field_presentation_location', 'location');
    $this->addFieldMapping('field_presentation_date', 'date');
    $this->addFieldMapping(OG_AUDIENCE_FIELD, OG_AUDIENCE_FIELD)
      ->sourceMigration(array('OsMigratePersonalNode', 'OsMigrateProjectNode'));

    $this->addFieldMapping(OG_VOCAB_FIELD, OG_VOCAB_FIELD)
      ->sourceMigration(array('OsMigrateScienceTaxonomyTerm'))
      ->separator('|');

    $this->addFieldMapping('uid', 'uid')
      ->sourceMigration('OsMigrateUsers');
  }

  public function prepare($entity, $row) {
    $entity->field_presentation_date[LANGUAGE_NONE][0] = array(
      'value' => $row->date,
      'date_type' => 'datetime',
    );
  }
}

/**
 * Migrate rss feeds.
 */
class OsMigrateFeedsNode extends OsMigrate {
  public $entityType = 'node';
  public $bundle = 'feed';

  public $csvColumns = array(
    array('id', 'ID'),
    array('title', 'Title'),
    array('body', 'Body'),
    array('address', 'Address'),
    array(OG_AUDIENCE_FIELD, 'Site'),
    array(OG_VOCAB_FIELD, 'Terms'),
    array('uid', 'UID'),
  );

  public $dependencies = array(
    'OsMigratePersonalNode',
    'OsMigrateProjectNode',
    'OsMigrateScienceTaxonomyTerm',
    'OsMigrateUsers',
  );

  public function __construct() {
    parent::__construct();

    $this->addFieldMapping('body', 'body');
    $this->addFieldMapping('address', 'field_url');
    $this->addFieldMapping(OG_AUDIENCE_FIELD, OG_AUDIENCE_FIELD)
      ->sourceMigration(array('OsMigratePersonalNode', 'OsMigrateProjectNode'));
    $this->addFieldMapping(OG_VOCAB_FIELD, OG_VOCAB_FIELD)
      ->sourceMigration(array('OsMigrateScienceTaxonomyTerm'))
      ->separator('|');

    $this->addFieldMapping('uid', 'uid')
      ->sourceMigration('OsMigrateUsers');
  }

  public function prepare($entity, $row) {
    $entity->field_url[LANGUAGE_NONE][0]['url'] = $row->address;
  }
}

/**
 * Migrate gallery feeds.
 */
class OsMigrateGalleryNode extends OsMigrate {
  public $entityType = 'node';
  public $bundle = 'media_gallery';

  public $csvColumns = array(
    array('id', 'ID'),
    array('title', 'Title'),
    array('body', 'Body'),
    array('images', 'Images'),
    array('destination', 'Destination'),
    array(OG_AUDIENCE_FIELD, 'Site'),
    array(OG_VOCAB_FIELD, 'Terms'),
    array('uid', 'UID'),
  );

  public $dependencies = array(
    'OsMigratePersonalNode',
    'OsMigrateProjectNode',
    'OsMigrateScienceTaxonomyTerm',
    'OsMigrateUsers',
  );

  public function __construct() {
    parent::__construct();

    // $this->addFieldMapping('body', 'body');
    $this->addFieldMapping(OG_AUDIENCE_FIELD, OG_AUDIENCE_FIELD)
      ->sourceMigration(array('OsMigratePersonalNode', 'OsMigrateProjectNode'));

    $this->addFieldMapping('media_gallery_file', 'images')
      ->separator(';');
    $this->addFieldMapping('media_gallery_file:file_replace')
      ->defaultValue(FILE_EXISTS_REPLACE);
    $this->addFieldMapping('media_gallery_file:source_dir')
      ->defaultValue(drupal_get_path('module', 'os_migrate_demo') . '/images');
    $this->addFieldMapping('media_gallery_file:destination_dir', 'destination');

    $this->addFieldMapping(OG_VOCAB_FIELD, OG_VOCAB_FIELD)
      ->sourceMigration(array('OsMigrateScienceTaxonomyTerm'))
      ->separator('|');

    $this->addFieldMapping('uid', 'uid')
      ->sourceMigration('OsMigrateUsers');
  }
}

/**
 * Migrate "Page" node.
 */
class OsMigratePageNode extends OsMigrate {
  public $entityType = 'node';
  public $bundle = 'page';

  public $csvColumns = array(
    array('id', 'ID'),
    array('title', 'Title'),
    array('body', 'Body'),
    array(OG_AUDIENCE_FIELD, 'Site'),
    array('uid', 'UID'),
  );

  public $dependencies = array(
    'OsMigratePersonalNode',
    'OsMigrateProjectNode',
    'OsMigrateUsers',
  );

  public function __construct() {
    parent::__construct();

    $this->addFieldMapping('body', 'body');
    $this->addFieldMapping(OG_AUDIENCE_FIELD, OG_AUDIENCE_FIELD)
      ->sourceMigration(array('OsMigratePersonalNode', 'OsMigratePersonalNode'));

    $this->addFieldMapping('uid', 'uid')
      ->sourceMigration('OsMigrateUsers');
  }
}

/**
 * Migrate Season status terms.
 */
class OsMigrateUsers extends Migration {
  /**
   * Map the field and properties to the CSV header.
   */
  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('name', 'Username'),
    array('pass', 'Password'),
    array('mail', 'Email'),
    array('first_name', 'First name'),
    array('last_name', 'Last name'),
    array('role', 'Role'),
  );

  public $entityType = 'user';

  public function __construct() {
    parent::__construct();
    $this->description = t('Import users from a CSV file.');

    $this->addFieldMapping('name', 'name');
    $this->addFieldMapping('pass', 'pass');
    $this->addFieldMapping('mail', 'mail');
    $this->addFieldMapping('field_first_name', 'first_name');
    $this->addFieldMapping('field_last_name', 'last_name');
    $this->addFieldMapping('roles')
      ->defaultValue(DRUPAL_AUTHENTICATED_RID);
    $this->addFieldMapping('status')
      ->defaultValue(TRUE);

    // Create a map object for tracking the relationships between source rows
    $key = array(
      'id' => array(
        'type' => 'varchar',
        'length' => 255,
        'not null' => TRUE,
      ),
    );
    $destination_handler = new MigrateDestinationUser();
    $this->map = new MigrateSQLMap($this->machineName, $key, $destination_handler->getKeySchema());

    // Create a MigrateSource object.
    $this->source = new MigrateSourceCSV(drupal_get_path('module', 'os_migrate_demo') . '/csv/' . $this->entityType . '/user.csv', $this->csvColumns, array('header_rows' => 1));
    $this->destination = new MigrateDestinationUser();
  }

  /**
   * Granting a role to the user from the CSV.
   */
  function complete($entity, $row) {
    if (!$row->role) {
      return;
    }

    $role = user_role_load_by_name($row->role);
    $entity->roles[$role->rid] = $row->role;

    user_save($entity);
  }
}

/**
 * Migrate OG-vocabs.
 *
 * @todo: Work in progress.
 */
class OsMigrateOgVocab extends OsMigrate {

  public $csvColumns = array(
    array('id', 'ID'),
    array('site', 'Site'),
    array('vocabulary', 'Vocabulary'),
    array('required', 'Required'),
    array('cardinality', 'Cardinality'),
    array('widget', 'Widget'),
  );

  public $entityType = 'og_vocab';
  public $bundle = 'og_vocab';

  public $dependencies = array(
    'OsMigrateAuthorsTaxonomyTerm',
    'OsMigrateBiologyTaxonomyTerm',
    'OsMigrateMathTaxonomyTerm',
    'OsMigrateScienceTaxonomyTerm',
  );

  protected $enabled = FALSE;

  public function __construct() {
    parent::__construct();

    $this->addFieldMapping('vocabulary', 'vocabulary');
    $this
      ->addFieldMapping(OG_AUDIENCE_FIELD, OG_AUDIENCE_FIELD)
      ->sourceMigration('OsMigratePersonalNode');

    $this->addFieldMapping('vid');
    $this->addFieldMapping('settings')->defaultValue(array());
  }

  public function prepareRow($row) {
    $name = $row->vocabulary . '_' . $row->{OG_AUDIENCE_FIELD};
    $vocabulary = taxonomy_vocabulary_machine_name_load($name);

    $row->vid = $vocabulary->vid;
    $row->entity_type = 'node';
    $row->bundle = 'class';

    $keys = array(
      'required',
      'cardinality',
      'widget',
    );
    foreach ($keys as $key) {
      $row->settings[$key] = $row->{$key};
    }
  }

  public function prepare($entity, $row) {
  }
}
