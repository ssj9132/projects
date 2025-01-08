import NewVisNav from '../Components/NewVisNav';
import InfoFilling from '../Components/InfoFilling'

export function NewVis() {
    return (
      <div className="Home">
        <nav>
          <NewVisNav />
        </nav>
        <body><InfoFilling /></body>

      </div>
    );
  }
  
  export default NewVis;