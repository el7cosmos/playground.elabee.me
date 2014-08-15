<?php
/**
 * @file
 * drupal_id_fb.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function drupal_id_fb_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function drupal_id_fb_node_info() {
  $items = array(
    'drupal_news' => array(
      'name' => t('Drupal News'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}

/**
 * Implements hook_default_wsclient_service().
 */
function drupal_id_fb_default_wsclient_service() {
  $items = array();
  $items['drupal'] = entity_import('wsclient_service', '{
    "settings" : [],
    "operations" : { "news" : {
        "url" : "node.json",
        "label" : "News",
        "parameter" : {
          "type" : { "type" : "text", "default value" : "forum" },
          "promote" : { "type" : "integer", "default value" : "1" },
          "taxonomy_forums" : { "type" : "integer" },
          "taxonomy_vocabulary_34" : { "type" : "integer" }
        },
        "name" : "news",
        "result" : { "type" : "news_lists", "label" : "" }
      }
    },
    "datatypes" : {
      "news_item" : {
        "label" : "News Item",
        "property info" : {
          "nid" : { "type" : "integer", "label" : "Node ID" },
          "title" : { "type" : "text", "label" : "Title" },
          "url" : { "type" : "uri", "label" : "URL" },
          "created" : { "type" : "integer", "label" : "Created" },
          "changed" : { "type" : "integer", "label" : "Changed" }
        },
        "name" : "item_list"
      },
      "news_lists" : {
        "label" : "News Lists",
        "property info" : { "list" : { "type" : "news_item", "label" : "" } },
        "name" : "news_lists"
      }
    },
    "global_parameters" : {
      "status" : { "default value" : "1" },
      "limit" : { "default value" : "10" },
      "sort" : { "default value" : "created" },
      "direction" : { "default value" : "DESC" }
    },
    "name" : "drupal",
    "label" : "Drupal",
    "url" : "https:\\/\\/www.drupal.org\\/api-d7\\/",
    "type" : "rest",
    "authentication" : null
  }');
  return $items;
}
