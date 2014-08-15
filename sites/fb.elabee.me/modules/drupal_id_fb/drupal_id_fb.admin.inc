<?php

/**
 * Form constructor for Drupal Indonesia Facebook Group settings form.
 *
 * @ingroup forms
 */
function drupal_id_fb_settings($form, &$form_state) {
  if ($token = fb_access_token()) {
    $form['drupal_id_fb_group'] = array(
      '#type' => 'radios',
      '#title' => 'Select group',
      '#options' => drupal_id_fb_user_groups($token),
      '#default_value' => variable_get('drupal_id_fb_group'),
    );

    $form['drupal_id_fb_message'] = array(
      '#type' => 'textarea',
      '#title' => 'Message',
      '#default_value' => variable_get('drupal_id_fb_message'),
    );

    return system_settings_form($form);
  }
  else {
    drupal_set_message(t('Missing access token, please configure <a href="@url">site wide access token</a>', array('@url' => url('admin/config/fb/settings/token'))), 'error');
  }
}

/**
 * Get available groups of facebook user
 *
 * @param  string $token
 *   Facebook access token.
 *
 * @return array
 *   An array of user's group keyed by group's id.
 *
 * @see fb_access_token()
 */
function drupal_id_fb_user_groups($token) {
  $response = fb_graph('me/groups', $token, FB_CACHE_QUERY_AND_STORE);

  $groups = array();
  if (isset($response['data'])) {
    foreach ($response['data'] as $data) {
      $groups[$data['id']] = $data['name'];
    }
  }

  return $groups;
}
