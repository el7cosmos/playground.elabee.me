<?php
/**
 * @file
 * drupal_id_fb.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function drupal_id_fb_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'drupal_news';
  $feeds_importer->config = array(
    'name' => 'Drupal News',
    'description' => '',
    'fetcher' => array(
      'plugin_key' => 'FeedsWSClientFetcher',
      'config' => array(
        'service_operation' => 'drupal:news',
        'operation_arguments' => array(
          'type' => 'forum',
          'promote' => '1',
          'taxonomy_forums' => '8',
          'taxonomy_vocabulary_34' => '903',
        ),
        'raw' => 0,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsWSClientParser',
      'config' => array(
        'context' => '|list',
        'sources' => array(),
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsUniqueNodeProcessor',
      'config' => array(
        'expire' => '-1',
        'author' => 0,
        'authorize' => 1,
        'mappings' => array(
          0 => array(
            'source' => 'title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          1 => array(
            'source' => 'url',
            'target' => 'url',
            'unique' => 1,
          ),
          2 => array(
            'source' => 'created',
            'target' => 'created',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '0',
        'input_format' => 'plain_text',
        'skip_hash_check' => 0,
        'bundle' => 'drupal_news',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '0',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['drupal_news'] = $feeds_importer;

  return $export;
}
