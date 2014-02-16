Feature: Testing OpenScholar calendar page.

  @api
  Scenario: Test the Calendar tab
    Given I visit "john"
     When I click "Calendar"
     Then I should see "Testing event"

  @api
  Scenario: Test the Calendar tab with month events
    Given I visit "john/calendar?month=2013-05&type=month"
     Then I should see "John F. Kennedy birthday"

  @api
  Scenario: Test the Calendar tab with day events filtered by terms.
    Given I visit "john/calendar?type=day&day=2013-05-29"
      And I should see the text "John F. Kennedy birthday" under "view-display-id-page_1"
     When I visit "john/calendar/authors/douglas-noël-adams?type=day&day=2013-05-29"
     Then I should not see the text "John F. Kennedy birthday" under "view-display-id-page_1"

  @api
  Scenario: Test the Calendar tab with week events filtered by terms.
    Given I visit "john/calendar/authors/stephen-william-hawking?week=2013-W22&type=week"
      And I should see the text "John F. Kennedy birthday" under "view-display-id-page_1"
     When I visit "john/calendar/authors/douglas-noël-adams?week=2013-W22&type=week"
     Then I should not see the text "John F. Kennedy birthday" under "view-display-id-page_1"

  @api
  Scenario: Test the Calendar tab with month events filtered by terms.
    Given I visit "john/calendar/authors/stephen-william-hawking?type=month&month=2013-05"
      And I should see the link "John F. Kennedy birthday" under "view-display-id-page_1"
     When I visit "john/calendar/authors/douglas-noël-adams?type=month&month=2013-05"
     Then I should not see the text "John F. Kennedy birthday" under "view-display-id-page_1"

  @api
  Scenario: Test the Calendar tab with year events filtered by terms.
    Given I visit "john/calendar/authors/stephen-william-hawking?type=year&year=2013"
      And I should see the link "29" under "has-events"
     When I visit "john/calendar/authors/douglas-noël-adams?type=year&year=2013"
     Then I should not see the link "29" under "view-display-id-page_1"

  @api
  Scenario: Testing the events export in iCal format.
    Given I visit "john/calendar/export.ics"
     Then I look for ".field_date.0@"

