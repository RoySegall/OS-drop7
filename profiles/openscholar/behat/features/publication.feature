Feature:
  Testing the publication tab and application.

  @api
  Scenario: Test the Publication tab
    Given I visit "john"
     When I click "Publications"
      And I click "The Little Prince"
     Then I should see "The Little Prince. United States; 1943."

  @api
  Scenario: Test the Publication tab allows caching of anonymous user
    Given cache is enabled for anonymous users
     When I visit "john/publications"
     Then I should get a "200" HTTP response
      And I visit "john/publications"
     Then response header "x-drupal-cache" should be "HIT"

  @api
  Scenario: Test the Authors field in Publication form
    Given I am logging in as "john"
     When I edit the node "The Little Prince"
     Then I should see "Authors"
      And I should see "Enter a single name per line"

  @api
  Scenario: Verify publications are sorted by the creation date of the node.
    Given I am logging in as "john"
     When I visit "john/publications"
     Then I should see the publication "Goblet of Fire" comes before "Prisoner of Azkaban"
      And I should see the publication "Prisoner of Azkaban" comes before "Chamber of Secrets"
      And I should see the publication "Chamber of Secrets" comes before "Philosophers Stone"

  @api
  Scenario: Verify sticky publications appear first on each section.
    Given I am logging in as "john"
      And I make the node "Philosophers Stone" sticky
     When I visit "john/publications"
      And I should see the publication "Philosophers Stone" comes before "Goblet of Fire"

