Feature:
  Testing the filter by term widget.

  @api
  Scenario: Verify that the user sees terms in the filter by term widget.
    Given I am logging in as "john"
    And the widget "Filter by term" is set in the "Publications" page with the following <settings>:
  | Vocabularies           | authors             | select list |
  | Show empty terms       | check               | checkbox    |
  | Show child terms       | check               | checkbox    |
  | Taxonomy tree depth.  | Show all children  | select list |
    When I visit "john/publications"
    Then I should see "Filter by term"
    And I should see the following <links>
      | Antoine de Saint-Exupéry |
      | Douglas Noël Adams       |
      | Antoine de Saint-Exupéry |

  @api
  Scenario: Verify that the number of tagged posts appended to the term name.
    Given I am logging in as "john"
    And I assign the node "John F. Kennedy" to the term "Antoine de Saint-Exupéry"
    And I assign the node "John F. Kennedy" to the term "Stephen William Hawking"
    And I set the term "Stephen William Hawking" under the term "Antoine de Saint-Exupéry"
    And I set the term "Douglas Noël Adams" under the term "Stephen William Hawking"
    And the widget "Filter by term" is set in the "Classes" page with the following <settings>:
  | Vocabularies                     | authors | select list |
  | Show empty terms                 | check   | checkbox    |
  | Show number of posts             | check   | checkbox    |
  | Show child terms                 | check   | checkbox    |
    When I visit "john/classes"
    Then I should see "Antoine de Saint-Exupéry (1)"
    And I should see "Stephen William Hawking (1)"

  @api
  Scenario: Verify the widget can show/hide the child terms.
    Given I am logging in as "john"
    And I set the term "Stephen William Hawking" under the term "Antoine de Saint-Exupéry"
    And I assign the node "John F. Kennedy" to the term "Stephen William Hawking"
    And the widget "Filter by term" is set in the "Publications" page with the following <settings>:
  | Vocabularies         | authors | select list |
  | Show empty terms     | check   | checkbox    |
  | Show child terms     | uncheck | checkbox    |
    And I visit "john/publications"
    And I should not see "Stephen William Hawking"
    And the widget "Filter by term" is set in the "Publications" page with the following <settings>:
  | Vocabularies         | authors | select list |
  | Show empty terms     | check   | checkbox    |
  | Show child terms     | check   | checkbox    |
    When I visit "john/publications"
    Then I should see "Stephen William Hawking"

  @api
  Scenario: Verify the widget can show/hide the child terms by the depth setting.
    Given I am logging in as "john"
    And I set the term "Stephen William Hawking" under the term "Antoine de Saint-Exupéry"
    And I set the term "Douglas Noël Adams" under the term "Stephen William Hawking"
    And the widget "Filter by term" is set in the "Publications" page with the following <settings>:
  | Vocabularies         | authors   | select list |
  | Show empty terms     | check     | checkbox    |
  | Show child terms     | check     | checkbox    |
  | Taxonomy tree depth. | 2nd Level | select list |
    And I visit "john/publications"
    And I should see "Antoine de Saint-Exupéry"
    And I should see "Stephen William Hawking"
    And I should not see "Douglas Noël Adams"
    And the widget "Filter by term" is set in the "Publications" page with the following <settings>:
  | Vocabularies         | authors   | select list |
  | Show empty terms     | check     | checkbox    |
  | Show child terms     | check     | checkbox    |
  | Taxonomy tree depth. | 3rd Level | select list |
    When I visit "john/publications"
    Then I should see "Antoine de Saint-Exupéry"
    And I should see "Stephen William Hawking"
    And I should see "Douglas Noël Adams"

  @api
  Scenario: Verify the widget can show/hide the child terms by the depth setting.
    Given I am logging in as "john"
    And the widget "Filter by term" is set in the "Publications" page with the following <settings>:
  | Vocabularies           | authors   | select list |
  | Show empty terms       | check     | checkbox    |
  | Show term descriptions | check     | checkbox    |
    When I visit "john/publications"
    Then I should get:
    """
    Antoine de Saint-Exupéry
    Wrote The little prince
    Stephen William Hawking
    Wrote A Brief History of Time
    Douglas Noël Adams
    Wrote The Hitchhiker's Guide to the Galaxy
    """

  @api
  Scenario: Verify the terms links direct us to the correct path.
    Given I am logging in as "john"
    And the widget "Filter by term" is set in the "Classes" page with the following <settings>:
  | Vocabularies           | authors   | select list |
  | Show empty terms       | check     | checkbox    |
  # We should set those terms upon migrate, instead of here.
    When I visit "john/classes"
    And I verify the "Stephen William Hawking" term link redirect to the original page
    Then I verify the "Antoine de Saint-Exupéry" term link doesn't redirect to the original page

  @api
  Scenario: Verify the terms links direct us to the correct path.
    Given I assign the node "Me and michelle obama" with the type "blog" to the term "Barack Hussein Obama"
    When I visit the original page for the term "Barack Hussein Obama"
    Then I should not get a "200" HTTP response

  @api
  Scenario: Verify that an empty term is shown if it has non-empty children.
    Given I am logging in as "john"
    And the widget "Filter by term" is set in the "Calendar" page with the following <settings>:
  | Widget Description   | Taxonomy  | textfield   |
  | Vocabularies         | authors   | select list |
  | Show empty terms     | uncheck   | checkbox    |
    And I set the term "Douglas Noël Adams" under the term "Antoine de Saint-Exupéry"
    And I set the term "Stephen William Hawking" under the term "Douglas Noël Adams"
    And I unassign the node "Halley's Comet" with the type "event" from the term "Douglas Noël Adams"
    When I visit "john/calendar"
    Then I should see "Douglas Noël Adams"
    And I should see "Antoine de Saint-Exupéry"
    And I should see "Stephen William Hawking"
