<?php

/**
 * @file
 * OS feed items fetcher for the feeds module.
 */
class OsFeedReaderFetcher extends FeedsProcessor {

  /**
   * Define entity type.
   */
  public function entityType() {
    return 'os_feed_item';
  }

  /**
   * Implements parent::entityInfo().
   */
  protected function entityInfo() {
    $info = parent::entityInfo();
    $info['label plural'] = t('OS feed items');
    return $info;
  }

  /**
   * Creates a new imported entity and returns it.
   */
  protected function newEntity(FeedsSource $source) {
    $os_reader = os_reader_feed_item_create();
    return $os_reader;
  }

  /**
   * Loads an existing imported entity.
   */
  protected function entityLoad(FeedsSource $source, $id) {
    $os_reader = os_reader_feed_item_load($id);
    return $os_reader;
  }

  /**
   * Save a imported entity.
   */
  protected function entitySave($entity) {
    $node = node_load($entity->feeds_item->feed_nid);
    $values = array(
      'title' => $entity->title,
      'description' => $entity->description,
      'created' => $entity->created,
      'guid' => $entity->feeds_item->guid,
      'url' => $entity->feeds_item->url,
      'importer_nid' => $entity->feeds_item->feed_nid,
      'importer_type' => $node->type == 'blog_import' ? 'blog' : 'news',
    );
    os_reader_feed_item_create($values)->save();
  }

  /**
   * Delete multiple user accounts.
   */
  protected function entityDeleteMultiple($ids) {
    os_reader_feed_item_delete_multiple($ids);
  }

  public function configDefaults() {
    return array(
      'type' => array(),
      'mappings' => array(),
    );
  }

  function configForm(&$form_state) {
    $form = array();
    return $form;
  }

  public function getMappingTargets() {
    $targets = array(
      'title' => array(
        'name' => t('Title'),
        'optional_unique' => TRUE,
      ),
      'description' => array(
        'name' => t('Description'),
      ),
      'image' => array(
        'name' => t('Image'),
      ),
      'created' => array(
        'name' => t('Published date'),
      ),
      'url' => array(
        'name' => t('URL'),
      ),
      'guid' => array(
        'name' => t('Item GUID'),
        'optional_unique' => TRUE,
      ),
    );

    self::loadMappers();
    $entity_type = $this->entityType();
    $bundle = 'os_feed_item';
    drupal_alter('feeds_processor_targets', $targets, $entity_type, $bundle);

    return $targets;
  }

  /**
   * Prevent duplication of entries.
   */
  protected function existingEntityId(FeedsSource $source, FeedsParserResult $result) {
    if ($id = parent::existingEntityId($source, $result)) {
      return $id;
    }

    $node = node_load($source->feed_nid);
    $wrapper = entity_metadata_wrapper('node', $node);
    $type = $wrapper->getBundle() == 'blog_import' ? 'blog' : 'news';

    $query = new entityFieldQuery();
    $results = $query
      ->entityCondition('entity_type', 'os_feed_item')
      ->propertyCondition('guid', $result->current_item['guid'])
      ->propertyCondition('importer_type', $type)
      ->fieldCondition(OG_AUDIENCE_FIELD, 'target_id', $wrapper->{OG_AUDIENCE_FIELD}->value(array('identifier' => TRUE)), 'IN')
      ->execute();

    if (!empty($results['os_feed_item'])) {
      return reset(array_keys($results['os_feed_item']));
    }

    return 0;
  }
}
