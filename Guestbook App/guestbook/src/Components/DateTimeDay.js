import { useState, useEffect } from 'react';

const DateTimeDay = () => {
  const [date, setDate] = useState(new Date());

  useEffect(() => {
    const timer = setInterval(() => {
      setDate(new Date());
    }, 1000);
    return () => clearInterval(timer);
  }, []);

  const day = date.toLocaleDateString('en-US', { weekday: 'long' });
  const month = date.toLocaleDateString('en-US', { month: 'long' });
  const dayOfMonth = date.toLocaleDateString('en-US', { day: 'numeric' });
  const year = date.toLocaleDateString('en-US', { year: 'numeric' });
  const timeString = date.toLocaleTimeString();

  const dateString = `${month} ${dayOfMonth} ${year}`;

  return (
    <p>{day}, {dateString}, {timeString}</p>
  );
};

export default DateTimeDay;
