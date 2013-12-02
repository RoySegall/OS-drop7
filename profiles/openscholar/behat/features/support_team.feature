Feature:
  Testing ability to subscribe as support team for privileged users,
  that creates an expirable membership.

  @api
  Scenario: Test subscribe for user with permission
    Given I am logging in as "bill"
    When I visit "obama"
    And I click "Support obama"
    And I press "Join"
    Then I should see "Unsubscribe Obama"

  @api
  Scenario: Test expiring membership on cron, of an existing member
    Given I am logging in as "bill"
    When I visit "obama"
    And I execute vsite cron
    Then I should not see "Support obama"

  @api
  Scenario: Test expiring membership on cron, of an existing member
    Given I am logging in as "bill"
    When I visit "obama"
    And I set the variable "vsite_support_expire" to "1 sec"
    And I execute vsite cron
    And I visit "obama"
    Then I should see "Support obama"

  @api
  Scenario: Test subscribe for user without permission
    Given I am logging in as "michelle"
    When I visit "obama"
    Then I should not see "Support obama"
