Feature:
  Testing the stats feature JSON ouput.

  @api
  Scenario: Verify for the json output for a specific node.
    Given I visit "stats"
      And I should get:
      """
      {"success":true,"websites":{"value":"{{*}}","text":"Websites"},"href":"{{*}}","os_version":"{{*}}"}
      """

  @api
  Scenario: Verify for the json output for a specific node.
    Given I visit "geckoboard"
    And I should get:
    """
    {"item":[{"value":"{{*}}","text":""}]}
    """
    When I visit "stats?style=geckoboard"
    Then I should get:
    """
    {"item":[{"value":"{{*}}","text":""}]}
    """
